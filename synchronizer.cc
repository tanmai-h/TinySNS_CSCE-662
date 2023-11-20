#include <ctime>

#include <google/protobuf/timestamp.pb.h>
#include <google/protobuf/duration.pb.h>
#include <chrono>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <mutex>
#include <stdlib.h>
#include <unistd.h>
#include <algorithm>
#include <google/protobuf/util/time_util.h>
#include <grpc++/grpc++.h>

#include "sns.grpc.pb.h"
#include "coordinator.grpc.pb.h"

namespace fs = std::filesystem;

using google::protobuf::Timestamp;
using google::protobuf::Duration;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using csce438::CoordService;
using csce438::ServerInfo;
using csce438::Confirmation;
using csce438::ID;
using csce438::ServerList;
using csce438::SynchService;
using csce438::UsersTLFL;

int synchID = 1;
std::vector<std::string> get_lines_from_file(std::string);
void run_synchronizer(std::string,std::string,std::string,int);
std::vector<std::string> get_all_users_func(int);
std::vector<std::string> get_tl_or_fl(int, int, bool);

class SynchServiceImpl final : public SynchService::Service {
    Status GetUsersTLFL(ServerContext* context, UsersTLFL* usersTlfl) override {
        std::vector<std::string> list = get_all_users_func(synchID);
        for(auto s:list){
            usersTlfl->add_users(s);
            std::vector<std::string> tl = get_tl_or_fl(synchID, clientID, true);
            std::vector<std::string> fl = get_tl_or_fl(synchID, clientID, false);
            for(auto timeline:tl){
                usersTlfl->add_tl(timeline);
            }
            for(auto follow:fl){
                usersTlfl->add_fl(follow);
            }
            usersTlfl->add_status(true); 
        }
        return Status::OK;
    }
};

void RunServer(std::string coordIP, std::string coordPort, std::string port_no, int synchID){
  //localhost = 127.0.0.1
  std::string server_address("127.0.0.1:"+port_no);
  SynchServiceImpl service;
  //grpc::EnableDefaultHealthCheckService(true);
  //grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  std::thread t1(run_synchronizer,coordIP, coordPort, port_no, synchID);
  /*
  TODO List:
    -Implement service calls
    -Set up initial single heartbeat to coordinator
    -Set up thread to run synchronizer algorithm
  */

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  
  int opt = 0;
  std::string coordIP;
  std::string coordPort;
  std::string port = "3029";

  while ((opt = getopt(argc, argv, "h:j:p:n:")) != -1){
    switch(opt) {
      case 'h':
          coordIP = optarg;
          break;
      case 'j':
          coordPort = optarg;
          break;
      case 'p':
          port = optarg;
          break;
      case 'n':
          synchID = std::stoi(optarg);
          break;
      default:
	         std::cerr << "Invalid Command Line Argument\n";
    }
  }

  RunServer(coordIP, coordPort, port, synchID);
  return 0;
}

void run_synchronizer(std::string coordIP, std::string coordPort, std::string port, int synchID) {
    //setup coordinator stub
    //std::cout<<"synchronizer stub"<<std::endl;
    std::string target_str = coordIP + ":" + coordPort;
    std::unique_ptr<CoordService::Stub> coord_stub_;
    coord_stub_ = std::unique_ptr<CoordService::Stub>(CoordService::NewStub(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials())));
    //std::cout<<"MADE STUB"<<std::endl;

    ServerInfo msg;
    Confirmation c;
    grpc::ClientContext context;

    msg.set_serverid(synchID);
    msg.set_hostname("127.0.0.1");
    msg.set_port(port);
    msg.set_type("follower");

    //send init heartbeat
    AllSyncServers allsyncservers;

    AllSyncServers allsyncservers;
    while(true) {
        //change this to 30 eventually
        sleep(30);
        grpc::Status status = coord_stub_->GetUsersTLFL(context, const google::protobuf::Empty, allsyncservers);
	    if (!status.ok()) {
            log(INFO, "Coord down ..");
            exit(-1);
        }
        for (const ServerInfo serverInfo : allsyncservers) {
           if (serverinfo.clusterID != synchID) {
                
           } 
        }
        for(auto i : aggregated_users) {
                //get currently managed users
                //if user IS managed by current synch
                    //read their follower lists
                    //for followed users that are not managed on cluster
                    //read followed users cached timeline
                    //check if posts are in the managed tl
                    //add post to tl of managed user    
            
                     // YOUR CODE HERE
            }
    }

    return;    
}

std::vector<std::string> get_lines_from_file(std::string filename){
  std::vector<std::string> users;
  std::string user;
  std::ifstream file; 
  file.open(filename);
  if(file.peek() == std::ifstream::traits_type::eof()){
    //return empty vector if empty file
    //std::cout<<"returned empty vector bc empty file"<<std::endl;
    file.close();
    return users;
  }
  while(file){
    getline(file,user);

    if(!user.empty())
      users.push_back(user);
  } 

  file.close();

  //std::cout<<"File: "<<filename<<" has users:"<<std::endl;
  /*for(int i = 0; i<users.size(); i++){
    std::cout<<users[i]<<std::endl;
  }*/ 

  return users;
}

bool file_contains_user(std::string filename, std::string user){
    std::vector<std::string> users;
    //check username is valid
    users = get_lines_from_file(filename);
    for(int i = 0; i<users.size(); i++){
      //std::cout<<"Checking if "<<user<<" = "<<users[i]<<std::endl;
      if(user == users[i]){
        //std::cout<<"found"<<std::endl;
        return true;
      }
    }
    //std::cout<<"not found"<<std::endl;
    return false;
}

std::vector<std::string> get_all_users_func(int synchID){
    //read all_users file master and client for correct serverID
    std::string master_users_file = "./master"+std::to_string(synchID)+"/all_users";
    std::string slave_users_file = "./slave"+std::to_string(synchID)+"/all_users";
    //take longest list and package into AllUsers message
    std::vector<std::string> master_user_list = get_lines_from_file(master_users_file);
    std::vector<std::string> slave_user_list = get_lines_from_file(slave_users_file);

    if(master_user_list.size() >= slave_user_list.size())
        return master_user_list;
    else
        return slave_user_list;
}

std::vector<std::string> get_tl_or_fl(int synchID, int clientID, bool tl){
    std::string master_fn = "./master"+std::to_string(synchID)+"/"+std::to_string(clientID);
    std::string slave_fn = "./slave"+std::to_string(synchID)+"/" + std::to_string(clientID);
    if(tl){
        master_fn.append("_timeline");
        slave_fn.append("_timeline");
    }else{
        master_fn.append("_follow_list");
        slave_fn.append("_follow_list");
    }

    std::vector<std::string> m = get_lines_from_file(master_fn);
    std::vector<std::string> s = get_lines_from_file(slave_fn);

    if(m.size()>=s.size()){
        return m;
    }else{
        return s;
    }

}