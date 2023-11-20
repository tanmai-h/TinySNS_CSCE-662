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
#include <google/protobuf/util/time_util.h>
#include <grpc++/grpc++.h>
#include<glog/logging.h>

#include "coordinator.grpc.pb.h"

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
using csce438::AllSyncServers;

#define log(severity, msg) LOG(severity) << msg; google::FlushLogFiles(google::severity); 

struct zNode{
  int serverID;
  std::string hostname = "localhost";
  std::string port;
  std::string type;
  std::time_t last_heartbeat;
  bool missed_heartbeat;
  bool isActive();
};

std::mutex v_mutex;
std::vector<zNode> cluster1;
std::vector<zNode> cluster2;
std::vector<zNode> cluster3;

std::unordered_map<int, std::vector<zNode>> routingTable = {};
std::vector<ServerInfo> syncServers;
//func declarations
int findServer(std::vector<zNode> v, int id);
std::time_t getTimeNow();
void checkHeartbeat();

bool zNode::isActive(){
    bool status = false;
    if(!missed_heartbeat){
        status = true;
    }else if(difftime(getTimeNow(),last_heartbeat) < 10){
        status = true;
    }
    return status;
}

class CoordServiceImpl final : public CoordService::Service {

  Status Heartbeat(ServerContext* context, const ServerInfo* serverInfo, Confirmation* confirmation) override {
      int cid = atoi(serverInfo->clusterid().c_str());
      if (routingTable.find(cid) == routingTable.end()) {
        confirmation->set_status(false);
        log(ERROR, "Invalid cid: " + std::to_string(cid));
        return grpc::Status(grpc::StatusCode::NOT_FOUND, std::string("Cluster ID: ") + std::to_string(serverInfo->serverid()) + std::string(" not found"));
      }

      zNode znode;
      znode.serverID = serverInfo->serverid();
      znode.port = serverInfo->port();
      znode.type = serverInfo->type();
      znode.last_heartbeat = getTimeNow();

      if(routingTable[cid].size() == 0) {
        znode.type = "master"; 
        routingTable[cid].push_back(znode);

      } else if (routingTable[cid].size() == 1) {
        znode.type = "slave";
        routingTable[cid].push_back(znode);        
      } else {
        if (znode.type == std::string("master")) {
          routingTable[cid][0] = znode;
        } else if (znode.type == std::string("slave")) {
          routingTable[cid][1] = znode;
        } else {
          routingTable[cid][0] = znode;
        }
      }

      log(INFO, "Got Heartbeat from clusterId, serverId: " + std::string(serverInfo->clusterid()) + std::string(",") + std::to_string(serverInfo->serverid()));
      confirmation->set_status(true);
      confirmation->set_type(znode.type);

      return Status::OK;
  }

  Status GetServer(ServerContext* context, const ID* id, ServerInfo* serverInfo) override {
    std::cout<<"Got request for clientID: "<<id->id()<<std::endl;
    int clusterID = (id->id()-1)%3+1;
    if (routingTable.find(clusterID) != routingTable.end()) {
      std::vector<zNode> cluster = routingTable[clusterID];
      for (auto c : cluster) {
        if (c.isActive()) {
          serverInfo->set_serverid(c.serverID);
          serverInfo->set_hostname(c.hostname);
          serverInfo->set_port(c.port);
          if (c.type == std::string("slave"))
            c.type = "master";
          serverInfo->set_type(c.type);
          break;
        } else {
          c.type = "down";
          return grpc::Status(grpc::StatusCode::UNAVAILABLE, "Server Not Available");
        }
      }
    } else {
      return grpc::Status(grpc::StatusCode::NOT_FOUND, "Clusted info not present in routing table");
    }
    return Status::OK;
  }

  Status GetSyncServers(ServerContext* context, const google::protobuf::Empty* request, AllSyncServers* allSyncServers) override {
    for (const ServerInfo sync : syncServers) {
      allSyncServers->add_servers()->CopyFrom(sync);
    }
    return Status::OK;
  }

  Status RegisterSyncServer(ServerContext* context, const ServerInfo* serverInfo, google::protobuf::Empty* response) override {
    syncServers.push_back(*serverInfo);
    return Status::OK;
  }
};

void RunServer(std::string port_no){
  //start thread to check heartbeats
  std::thread hb(checkHeartbeat);
  //localhost = 127.0.0.1
  std::string server_address("127.0.0.1:"+port_no);
  CoordServiceImpl service;
  //grpc::EnableDefaultHealthCheckService(true);
  //grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  routingTable[1] = std::vector<zNode>();
  routingTable[2] = std::vector<zNode>();
  routingTable[3] = std::vector<zNode>();
  
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Coordinator listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  
  std::string port = "9090";
  int opt = 0;
  while ((opt = getopt(argc, argv, "p:")) != -1){
    switch(opt) {
      case 'p':
          port = optarg;
          break;
      default:
	std::cerr << "Invalid Command Line Argument\n";
    }
  }
  std::string log_file_name = std::string("coordinator-port-") + port;  
  google::InitGoogleLogging(log_file_name.c_str());

  RunServer(port);
  return 0;
}

void checkHeartbeat() {
  while (true) {
      for (auto& clusterPair : routingTable) {
          for (zNode& server : clusterPair.second) {
              if (server.isActive() && difftime(getTimeNow(), server.last_heartbeat) > 10) {
                  server.missed_heartbeat = true;
              } else if (!server.isActive() && difftime(getTimeNow(), server.last_heartbeat) <= 10) {
                  server.missed_heartbeat = false;
              }
          }
      }
      sleep(1);  // Sleep for 3 seconds before checking again
  }
}

std::time_t getTimeNow(){
    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}