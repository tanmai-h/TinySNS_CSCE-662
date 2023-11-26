/*
 *
 * Copyright 2015, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <ctime>

#include <google/protobuf/timestamp.pb.h>
#include <google/protobuf/duration.pb.h>

#include <fstream>
#include <thread>
#include <iostream>
#include <memory>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <google/protobuf/util/time_util.h>
#include <grpc++/grpc++.h>
#include "coordinator.grpc.pb.h"
#include <glog/logging.h>
#include "sns.grpc.pb.h"

#define log(severity, msg) LOG(severity) << msg; google::FlushLogFiles(google::severity); 

using google::protobuf::Timestamp;
using google::protobuf::Duration;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ClientContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
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

struct Client {
  std::string username;
  bool connected = true;
  std::vector<Client*> client_followers;
  std::vector<Client*> client_following;
  ServerReaderWriter<Message, Message>* stream = 0;
  bool operator==(const Client& c1) const{
    return (username == c1.username);
  }
};
 
//Vector that stores every client that has been created
std::vector<Client*> client_db;
std::shared_ptr<CoordService::Stub> channel;
ServerInfo serverInfo;
std::unordered_set<std::string> current_users = {};
std::unordered_map<std::string, std::vector<std::string>> user_timeline = {};

std::vector<std::string> get_lines_from_file(std::string filename) {
  std::vector<std::string> users;
  std::string user;
  std::ifstream file; 
  file.open(filename);
  if(file.peek() == std::ifstream::traits_type::eof()){
    file.close();
    return users;
  }
  while(file){
    getline(file,user);

    if(!user.empty())
      users.push_back(user);
  } 

  file.close();

  return users;
}

//Helper function used to find a Client object given its username
int find_user(std::string username){ 
  int index = 0;
  for(Client* c : client_db){
    if(c->username == username)
      return index;
    index++;
  }
  return -1;
}

bool isincurrent(std::string username) {
      int cluster = ((atoi(username.c_str()))-1)%3+1;
    return std::to_string(cluster) == ::serverInfo.clusterid();

}

std::string getfilename(std::string clientid = "current", bool getother=false) {
    std::string n = "";
    std::string server_type = ::serverInfo.type();
    if (getother) 
      server_type = (server_type == "master") ? "slave"  : "master";
    if(clientid == "current") {
      n = "./" + server_type + "_" + ::serverInfo.clusterid() + "_currentusers.txt";
    }
    else if (clientid == "all") {
      n = "./" + server_type + "_" + ::serverInfo.clusterid() + "_allusers.txt";
    } else {
      n = "./" + server_type + "_" + ::serverInfo.clusterid() + "_" + clientid;
    }
    return n;
}

void copier(){
    std::vector<std::string> cusers;
    std::string tmp;
    std::vector<std::string> fnames = {"current", "all"};
    for (auto s : fnames) {
      std::ifstream source(getfilename(s, true), std::ios::binary);
      std::ofstream dest(getfilename(s), std::ios::binary);
      dest << source.rdbuf();
      source.close(); dest.close();
    }
    std::ifstream source(getfilename("current", true), std::ios::in);
    while(getline(source, tmp)) {
      cusers.push_back(tmp);
      current_users.insert(tmp);
    }
    source.close();
    fnames = {"_timeline.txt", "_follower.txt", "_following.txt", ".txt"};
    for (auto s : cusers) {
      std::string base = getfilename(s,true);
      std::string dbase = getfilename(s);
      for (auto fn : fnames) {
        std::ifstream source (base  + fn,  std::ios::binary);
        std::ofstream dest   (dbase + fn,  std::ios::binary);
        dest << source.rdbuf();
        source.close(); dest.close();
      }
    }
}

class SNSServiceImpl final : public SNSService::Service {
  Status List(ServerContext* context, const Request* request, ListReply* list_reply) override {
    log(INFO,"Serving List Request from: " + request->username()  + "\n");
    std::cout << " Serving List Request from: " << request->username() << "\n";
    std::ifstream in(getfilename("all"), std::ios::in | std::ios::out);
    std::string user;
    while(getline(in,user)) {
      list_reply->add_all_users(user);
    }
    in.close();
    in = std::ifstream(getfilename(request->username())+"_follower.txt");
    std::cout << "follower: \n";
    while(getline(in,user)) {
      std::cout << "\t" << user << "\n";
      list_reply->add_followers(user);
    }
    in.close();  
    return Status::OK;
  }

  Status Follow(ServerContext* context, const Request* request, Reply* reply) override {
    std::string username1 = request->username();
    std::string username2 = request->arguments(0);
    log(INFO,"Serving Follow Request from: " + username1 + " for: " + username2 + "\n");
    int join_index = find_user(username2);
    if(username1 == username2)
      reply->set_msg("Join Failed -- Invalid Username");
    else {
      Client *user1 = client_db[find_user(username1)];
      Client *user2 = nullptr;
      if (join_index >= 0) {
        user2 = client_db[join_index];
        user1->client_following.push_back(user2);
        user2->client_followers.push_back(user1);
        std::ofstream flr(getfilename(user2->username)+"_follower.txt", std::ios::app);
        flr << username1 << "\n";
        flr.close();
      }
      std::ofstream flw(getfilename(user1->username)+"_following.txt", std::ios::app);
      flw << username2 << "\n";
      flw.close();
      reply->set_msg("Follow Successful");
    }
    return Status::OK;
  }

  Status UnFollow(ServerContext* context, const Request* request, Reply* reply) override {
    std::string username1 = request->username();
    std::string username2 = request->arguments(0);
    log(INFO,"Serving Unfollow Request from: " + username1 + " for: " + username2);
 
    int leave_index = find_user(username2);
    if(username1 == username2) {
      reply->set_msg("Unknown follower");
    }
    return Status::OK;
  }

  Status Login(ServerContext* context, const Request* request, Reply* reply) override {
    Client* c = new Client();
    std::string username = request->username();
    log(INFO, "Serving Login Request: " + username + "\n");
    int user_index = find_user(username);
    if(user_index < 0){
      c->username = username;
      client_db.push_back(c);
      reply->set_msg("Login Successful!");
      for (auto c : current_users) {
        std::cout << " prev current " << c << "\n";
      }
      if(current_users.find(username) == current_users.end()) {
          std::ofstream current(getfilename("current"),std::ios::app|std::ios::out|std::ios::in);
          current << username << "\n";
          current.close();
          current_users.insert(username);
          std::ofstream all(getfilename("all"),std::ios::app|std::ios::out|std::ios::in);
          all << username << "\n";
          all.close();
      }
    } else {
      Client *user = client_db[user_index];
      current_users.insert(user->username);
      if(user->connected) {
        log(WARNING, "User already logged on");
        std::string msg = "Welcome Back " + user->username;
        reply->set_msg(msg);
      } else{
        std::string msg = "Welcome Back " + user->username;
        reply->set_msg(msg);
        user->connected = true;
      }
    }

    return Status::OK;
  }

  Status Timeline(ServerContext* context, ServerReaderWriter<Message, Message>* stream) override {
    log(INFO,"Serving Timeline Request");
    Message message;
    Client *c;
    while(stream->Read(&message)) {
      std::string username = message.username();
      int user_index = find_user(username);
      c = client_db[user_index];
      c->stream = stream;
      std::string filename = getfilename(username) + ".txt";
      std::ofstream user_file(filename, std::ios::app|std::ios::out|std::ios::in);
      google::protobuf::Timestamp temptime = message.timestamp();
      std::string time = google::protobuf::util::TimeUtil::ToString(temptime);
      std::string fileinput = message.username() + std::string(" (") + time + std::string(") >> ") + message.msg() + "\n";
      //"Set Stream" is the default message from the client to initialize the stream
      if(message.msg() != "Set Stream") {
        user_file << fileinput;
        user_file.close();
      }
      //If message = "Set Stream", print the first 20 chats from the people you follow
      else {
        std::string line;
        std::vector<std::string> newest_twenty;
        std::ifstream in(getfilename(username)+"_timeline.txt");
        int count = 0;
        //Read the last up-to-20 lines (newest 20 messages) from userfollowing.txt
        while(getline(in, line)){
          newest_twenty.push_back(line);
        }
        Message new_msg; 
 	      //Send the newest messages to the client to be displayed
 	      if(newest_twenty.size() >= 40) {
          for(int i = newest_twenty.size()-40; i<newest_twenty.size(); i+=2){
            new_msg.set_msg(newest_twenty[i]);
            stream->Write(new_msg);
          }
        } else{
          for(int i = 0; i < newest_twenty.size(); i += 2) {
            new_msg.set_msg(newest_twenty[i]);
            stream->Write(new_msg);
	        }
        }
        continue;
      }
      //Send the message to each follower's stream in current cluster
      std::vector<Client*>::const_iterator it;
      std::ifstream infile(getfilename(c->username)+"_follower.txt");
      std::string follower;
      while (getline(infile, follower)) {
        int idx = find_user(follower);
        if (idx >= 0) {
          Client * temp_client =  client_db[idx];
          if(temp_client->stream) 
                temp_client->stream->Write(message);
          std::string temp_username = temp_client->username;
          if (isincurrent(temp_username)) {
              std::string temp_file = getfilename(temp_username) + "_timeline.txt";
              std::ofstream user_file(temp_file,std::ios::app|std::ios::out|std::ios::in);
              user_file << fileinput;
              user_file.close();
          }
        }
      }
    }
    //If the client disconnected from Chat Mode, set connected to false
    c->connected = false;
    return Status::OK;
  }
};

class HeartbeatClient {
public:
  HeartbeatClient() {}
  HeartbeatClient(const std::string& serverAddress, ServerInfo &serverInfo)
      : serverAddress_(serverAddress), serverInfo_(serverInfo){
      channel_ = grpc::CreateChannel(serverAddress_, grpc::InsecureChannelCredentials());
      stub_ = CoordService::NewStub(channel_);
  }

  void SendHeartbeat() {
      grpc::ClientContext clientContext;
      Confirmation confirmation;
      grpc::Status grpcStatus = stub_->Heartbeat(&clientContext, serverInfo_, &confirmation);
      if (!grpcStatus.ok() || !confirmation.status()) {
        log(ERROR, "Could not get the correct reply for Heartbeat from Coordinator");
        exit(-1);
      }
      if (::serverInfo.type() == "slave" && confirmation.type() == "master") {
        copier();
      }
      serverInfo_.set_type(confirmation.type());
      ::serverInfo.set_type(confirmation.type());
      std::cout << "Recevied confirmation for heartbeat, now type= " << confirmation.type() << "\n";
      log(INFO, "Got confirmation from cooridinator  now type=" + confirmation.type());
  }

  private:
      std::string serverAddress_;
      ServerInfo serverInfo_;
      std::shared_ptr<grpc::Channel> channel_;
      std::unique_ptr<CoordService::Stub> stub_;
};

void sendHeartbeatThread(HeartbeatClient& client) {
   bool firstb = false;
   try {
      while (true) {
          client.SendHeartbeat();
          if (!firstb) {}
          std::this_thread::sleep_for(std::chrono::seconds(10));  // Adjust the interval as needed.
      }
   } catch(const std::exception &e) {
      log(ERROR, " exception in sending heartbeat= " + std::string(e.what()));
   }
}

void updateTimelineStream() {
  while (true) {
    for (auto &c : get_lines_from_file(getfilename("current"))) {
      std::ifstream ifs((getfilename(c) + "_timeline.txt"), std::ios::in);
      std::string tmp;
      std::vector<std::string> tl;
      while (getline(ifs, tmp))
        tl.push_back(tmp);
      ifs.close();

      std::vector<std::string> msg = {};
      if (user_timeline.find(c) == user_timeline.end())
        user_timeline[c] = {};
      for (int i = 0; i < tl.size(); i+=2) {
        auto msg = tl[i];
        std:: cout << " USER= " << c << " CHECKING_FOR_UPDATE= " << msg << "\n";
        if (find(user_timeline[c].begin(), user_timeline[c].end(), msg) == user_timeline[c].end()) {
          user_timeline[c].push_back(tl[i]);
          int idx = find_user(c);
          if (idx >= 0) {
            if(client_db[idx]->stream) {
              Message new_msg;
                new_msg.set_msg(msg);
              client_db[idx]->stream->Write(new_msg);
            }
          }
        }
      }
    }
    sleep(15);
  }
}

class ServerProvider {
public:
    // Constructor with parameters to initialize member variables
    ServerProvider(const std::string& port, const std::string& clusterId, const std::string& serverId, const std::string& coordinatorIP, const std::string& coordinatorPort)
        : port(port), clusterId(clusterId), serverId(serverId), coordinatorIP(coordinatorIP), coordinatorPort(coordinatorPort) {
    }

    void Run() {
        connectToCoordinator();
        sleep(5);
        std::vector<std::string> all = get_lines_from_file(getfilename("all")),
              current = get_lines_from_file(getfilename("current"))
        ;
        for (auto s : current) {
          std::cout << " adding  - " << s << "\n";
          current_users.insert(s);
        }
        RunServer();
    }

    ~ServerProvider() {
      if(ht.joinable())
          ht.join();
      if (timelineThread.joinable())
        timelineThread.join();
    }
private:
    std::string port;
    std::string clusterId;
    std::string serverId;
    std::string coordinatorIP;
    std::string coordinatorPort;
    HeartbeatClient hc;
    std::thread ht, timelineThread;
  
    int connectToCoordinator() {
      try {
        serverInfo.set_serverid(std::stoi(serverId));
        serverInfo.set_hostname("127.0.0.1");
        serverInfo.set_port(port);
        serverInfo.set_type("new");
        serverInfo.set_clusterid(clusterId);
        std::string coordLoginInfo = coordinatorIP + ":" + coordinatorPort;
        hc = HeartbeatClient(coordLoginInfo, serverInfo);
        ht = std::thread(sendHeartbeatThread, std::ref(hc));
        timelineThread = std::thread(updateTimelineStream);
        return 0;
      } catch (const std::exception& e) {
          log(ERROR, "Exception in connectToCoordinator: " + std::string(e.what()));
          return -1; // Return an error code to indicate failure
        }
    }

     void RunServer() {
        std::thread();
        std::string server_address = "127.0.0.1:" + port;
        SNSServiceImpl service;
        ServerBuilder builder;
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);
        std::unique_ptr<Server> server(builder.BuildAndStart());
        std::cout << "Server listening on " << server_address << std::endl;
        log(INFO, "Server listening on: " + server_address);

        server->Wait();
    }
};

int main(int argc, char** argv) {
  std::string port = "10000";
  std::string clusterId = "1";
  std::string serverId = "1";
  std::string coordinatorIP = "127.0.0.1";
  std::string coordinatorPort = "9090";
  int opt = 0;
  while ((opt = getopt(argc, argv, "c:s:h:k:p:")) != -1){
    switch(opt) {
      case 'c':
        clusterId = optarg;
        break;
      case 's':
        serverId = optarg;
        break;
      case 'h':
        coordinatorIP = optarg;
        break;
      case 'k':
        coordinatorPort = optarg;
        break;
      case 'p':
        port = optarg;
        break;
      default:
        std::cerr << "Invalid Command Line Argument\n";
        return 1; // Exit with an error code
    }
  }
  
  std::string log_file_name = std::string("cluster-") + clusterId + std::string("-server-") + serverId + "-port-" + port;
  google::InitGoogleLogging(log_file_name.c_str());
  log(INFO, "Logging Initialized. Server starting...");

  ServerProvider serverProvider(port, clusterId, serverId, coordinatorIP, coordinatorPort);
  serverProvider.Run();

  return 0;
}