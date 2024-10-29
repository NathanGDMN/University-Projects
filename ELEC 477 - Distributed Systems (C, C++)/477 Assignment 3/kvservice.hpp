

#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector> //For vector to hold replica info pairs
#include <utility>  //For pairs to hold replica information
#include <arpa/inet.h>
#include <sys/socket.h>

#ifdef __APPLE__
#include <ndbm.h>
#else
#include <gdbm.h>
#endif


#include "KVrpc.h"
#include "E477KV.pb.h"
#include "dumpHex.hpp"
#include "network.hpp"
#include "servicedir/srvcdirclientstub.hpp"

using namespace std;


class KVServiceServer: public Service{
    // system state
    string DBMFileName;
#ifdef __APPLE__
    DBM * dataFile = NULL;
#else
    GDBM_FILE dataFile;
#endif
    
    // rpc specific values
    // version 1.0
    static const uint32_t magic = 'E477';
    static const uint32_t version1x = 0x0100;

    // service Dir Management
    string svcName;
    SvcDirClientStub svcDirService;

    // network management
    int sockfd;
    in_port_t port = 8080;
    static const int MAXMSG = 1400;
    uint8_t udpMessage[MAXMSG];
    
    void callMethodVersion1(E477KV::kvRequest &receivedMsg, E477KV::kvResponse &replyMsg);
    
    //key value management
    bool kvPut(int key, const uint8_t * value, uint16_t vlen);
    kvGetResult kvGet(int key);

    // primary management
    bool primary;
    vector<pair<string, in_port_t>> replicas;
    void propagateMessage(E477KV::kvRequest &receivedMsg, in_port_t port);
    
public:
    KVServiceServer(string name, weak_ptr<Node> p):Service(name + ".KV_RPC" ,p),svcDirService(name+".svcDirstub"){ }
    ~KVServiceServer(){
        stop();
        
        // bug in alive flag prevents this from being reached.
#ifdef __APPLE__
        if (dataFile != nullptr) {
            dbm_close(dataFile);
            dataFile = nullptr;
        }
#else
        if (dataFile != nullptr) {
            gdbm_close(dataFile);
            dataFile = nullptr;
	}
#endif
        
    }
    void start();
    void stop();
    
    void setDBMFileName(string name) {DBMFileName = "data/" + name;}
    void setServiceDirServer(string addr);
    void setServiceName(string svcName);
    void setPort(in_port_t p) { port = p;}

    // primary management
    void setPrimary(bool inputBool);
    void addReplica(string replicaName, in_port_t port);
};

#endif
