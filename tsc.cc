#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <string>
#include <unistd.h>
#include <csignal>
#include <grpc++/grpc++.h>
#include "client.h"
#include "coordinator.grpc.pb.h"
#include "sns.grpc.pb.h"
using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using csce438::Message;
using csce438::ListReply;
using csce438::Request;
using csce438::Reply;
using csce438::SNSService;
using csce438::CoordService;
using csce438::ServerInfo;
using csce438::Confirmation;
using csce438::ID;

Message MakeMessage(const std::string& username, const std::string& msg) {
    Message m;
    m.set_username(username);
    m.set_msg(msg);
    google::protobuf::Timestamp* timestamp = new google::protobuf::Timestamp();
    timestamp->set_seconds(time(NULL));
    timestamp->set_nanos(0);
    m.set_allocated_timestamp(timestamp);
    return m;
}

class Client : public IClient {
public:
  Client(const std::string& hname,
	 const std::string& uname,
	 const std::string& p)
    :cip(hname), uid(uname), cport(p) {}

  
protected:
  virtual int connectTo();
  virtual IReply processCommand(std::string& input);
  virtual void processTimeline();

private:
  std::string cip;
  std::string uid;
  std::string cport;
  
  // You can have an instance of the client stub
  // as a member variable.
  std::unique_ptr<SNSService::Stub> stub_;
  std::unique_ptr<CoordService::Stub> coordStub;

  IReply Login();
  IReply List();
  IReply Follow(const std::string &username);
  IReply UnFollow(const std::string &username);
  void   Timeline(const std::string &username);
};

int Client::connectTo() {
    std::string login_info = cip + ":" + cport;
  
    coordStub = CoordService::NewStub(grpc::CreateChannel(
          login_info, grpc::InsecureChannelCredentials()
        ));

    ClientContext clientContext;
    ServerInfo serverInfo;
    ID id;
    id.set_id(atoi(uid.c_str()));
    grpc::Status grpcStatus = coordStub->GetServer(&clientContext,id,&serverInfo);
    if (!grpcStatus.ok()) {
      return -1;
    }

    login_info = serverInfo.hostname() + ":" + serverInfo.port();

    stub_ = std::unique_ptr<SNSService::Stub>(SNSService::NewStub(
        grpc::CreateChannel(
        login_info, grpc::InsecureChannelCredentials())));
    
    IReply ire = Login();
    if(!ire.grpc_status.ok() || (ire.comm_status == FAILURE_ALREADY_EXISTS)) {
      return -1;
    }
    return 1;
}

IReply Client::processCommand(std::string& input)
{

  IReply ire;
  std::size_t index = input.find_first_of(" ");
  std::cout << "Processing "+input + ". ";
  if (index != std::string::npos) {
    std::string cmd = input.substr(0, index);
        
    std::string argument = input.substr(index+1, (input.length()-index));
    
    if (cmd == "FOLLOW") {
      return Follow(argument);
    } else if(cmd == "UNFOLLOW") {
      return UnFollow(argument);
    }
  } else {
    if (input == "LIST") {
      return List();
    } else if (input == "TIMELINE") {
      IReply tmpre = List();
      // If the server is down, we want the grpc status to not be OK
      if (!tmpre.grpc_status.ok()){
        ire.comm_status = FAILURE_UNKNOWN;
        return ire;
      }
      ire.comm_status = SUCCESS;
      return ire;
    }
  }
  
  ire.comm_status = FAILURE_INVALID;
  return ire;
}

void Client::processTimeline()
{
    Timeline(uid);
    // ------------------------------------------------------------
    // In this function, you are supposed to get into timeline mode.
    // You may need to call a service method to communicate with
    // the server. Use getPostMessage/displayPostMessage functions
    // for both getting and displaying messages in timeline mode.
    // You should use them as you did in hw1.
    // ------------------------------------------------------------

    // ------------------------------------------------------------
    // IMPORTANT NOTICE:
    //
    // Once a user enter to timeline mode , there is no way
    // to command mode. You don't have to worry about this situation,
    // and you can terminate the client program by pressing
    // CTRL-C (SIGINT)
    // ------------------------------------------------------------

}

IReply Client::List() {
    //Data being sent to the server
    Request request;
    request.set_username(uid);

    //Container for the data from the server
    ListReply list_reply;

    //Context for the client
    ClientContext context;

    Status status = stub_->List(&context, request, &list_reply);
    IReply ire;
    ire.grpc_status = status;

    //Loop through list_reply.all_users and list_reply.following_users
    //Print out the name of each room
    if(status.ok()){
        ire.comm_status = SUCCESS;
        std::string all_users;
        std::string following_users;
        for(std::string s : list_reply.all_users()){
            ire.all_users.push_back(s);
        }
        for(std::string s : list_reply.followers()){
            ire.followers.push_back(s);
        }
    }
    return ire;
}
        
IReply Client::Follow(const std::string& username2) {
    Request request;
    request.set_username(uid);
    request.add_arguments(username2);

    Reply reply;
    ClientContext context;

    Status status = stub_->Follow(&context, request, &reply);
    IReply ire; ire.grpc_status = status;
    if (reply.msg() == "unkown user name") {
        ire.comm_status = FAILURE_INVALID_USERNAME;
    } else if (reply.msg() == "unknown follower username") {
        ire.comm_status = FAILURE_INVALID_USERNAME;
    } else if (reply.msg() == "you have already joined") {
        ire.comm_status = FAILURE_ALREADY_EXISTS;
    } else if (reply.msg() == "Follow Successful") {
        ire.comm_status = SUCCESS;
    } else {
        ire.comm_status = FAILURE_UNKNOWN;
    }
    return ire;
}

IReply Client::UnFollow( const std::string& username2) {
    Request request;

    request.set_username(uid);
    request.add_arguments(username2);

    Reply reply;

    ClientContext context;

    Status status = stub_->UnFollow(&context, request, &reply);
    IReply ire;
    ire.grpc_status = status;
    if (reply.msg() == "Unknown follower") {
        ire.comm_status = FAILURE_INVALID_USERNAME;
    } else if (reply.msg() == "You are not a follower") {
        ire.comm_status = FAILURE_NOT_A_FOLLOWER;
    } else if (reply.msg() == "UnFollow Successful") {
        ire.comm_status = SUCCESS;
    } else {
        ire.comm_status = FAILURE_UNKNOWN;
    }

    return ire;
}

IReply Client::Login() {
    Request request;
    request.set_username(uid);
    Reply reply;
    ClientContext context;

    Status status = stub_->Login(&context, request, &reply);

    IReply ire;
    ire.grpc_status = status;
    std::cout << "REPLY MESSAGE: " + reply.msg();
    if (reply.msg() == "you have already joined") {
        ire.comm_status = FAILURE_ALREADY_EXISTS;
    } else {
        ire.comm_status = SUCCESS;
    }
    return ire;
}

void Client::Timeline(const std::string& username) {
  ClientContext context;

  std::shared_ptr<ClientReaderWriter<Message, Message>> stream(
				  stub_->Timeline(&context));

  //Thread used to read chat messages and send them to the server
  std::thread writer([username, stream]() {
    std::string input = "Set Stream";
    Message m = MakeMessage(username, input);
    stream->Write(m);
    while (1) {
      input = getPostMessage();
      m = MakeMessage(username, input);
      stream->Write(m);
    }
    stream->WritesDone();
  });
  
  std::thread reader([username, stream]() {
    Message m;
    while(stream->Read(&m)){
      google::protobuf::Timestamp temptime = m.timestamp();
      std::time_t time = temptime.seconds();
      displayPostMessage(m.username(), m.msg(), time);
    }
  });
  
  //Wait for the threads to finish
  writer.join();
  reader.join();
}

int main(int argc, char** argv) {

  std::string cip = "127.0.0.1";
  std::string cport = "9090";
  std::string uid = "1";
    
  int opt = 0;
  while ((opt = getopt(argc, argv, "h:k:u:")) != -1){
    switch(opt) {
    case 'h':
      cip = optarg;break;
    case 'k':
      cport = optarg;break;
    case 'u':
      uid = optarg;break;
    default:
      std::cout << "Invalid Command Line Argument\n";
    }
  }

  std::cout << "Logging Initialized. Client starting...";
  
  Client myc(cip, uid, cport);

  myc.run();
  
  return 0;
}
