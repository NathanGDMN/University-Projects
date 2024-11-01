#ifndef __SDSTUB_HPP_
#define __SDSTUB_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <atomic>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "SDrpc.h"
#include "E477KV.pb.h"
#include "dumpHex.hpp"


using namespace std;

class SDServiceStub{
    // system managment values
    string name;
    bool ready;
    string serverAddrString;
    string serverName;

    // rpc specific values
    // version 1.0
    static const uint32_t magic = 'E477';
    static const uint32_t version1x = 0x0100;
    atomic<uint32_t> serial;

     // network management
    int sockfd;
    static const in_port_t PORT = 8080;
    static const int MAXMSG = 1400;
    uint8_t udpMessage[MAXMSG];
    struct sockaddr_in	 servaddr;

    bool init();

public:
    SDServiceStub(string name ): name(name),ready(false), serial(1){
    }
    ~SDServiceStub(){
        shutdown();
    }
    void shutdown();
    void setServerAddress(string address){
        serverAddrString = address;
    }
    void setServerName(string name){
        serverName = name;
    }
    // bool kvPut(int32_t, const uint8_t* value, uint16_t vlen);
    // kvGetResult kvGet(int32_t);
    //New Stuff:
    bool sdput(string serviceName, string servername, int port);
    sdGetResult sdget(string serviceName);
    bool sddelete(string serviceName);
};

#endif

