#ifndef _SDSERVICE_HPP_
#define _SDSERVICE_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>

//Assignment specific stuff:
#include "SDrpc.h"
#include "E477KV.pb.h"
#include "dumpHex.hpp"
#include "network.hpp"

#include <map> //Will use this to store values

using namespace std;

class SDServiceServer: public Service{
    // rpc specific values
    // version 1.0
    static const uint32_t magic = 'E477';
    static const uint32_t version1x = 0x0100;

    // network management
    int sockfd;
    in_port_t PORT = 8080;
    static const int MAXMSG = 1400;
    uint8_t udpMessage[MAXMSG];
    
    //Old Stuff:
    // void callMethodVersion1(E477KV::kvRequest &receivedMsg, E477KV::kvResponse &replyMsg);
    // bool kvPut(int key, const uint8_t * value, uint16_t vlen);
    // kvGetResult kvGet(int key);

    //New Stuff:
    bool sdput(string serviceName, string servername, int port);
    sdGetResult sdget(string serviceName);
    bool sddelete(string serviceName);
    
public:
    SDServiceServer(string name, weak_ptr<Node> p):Service(name + ".SD_RPC" ,p){ }
    ~SDServiceServer(){
        stop();
    }
    void start();
    void stop();
};