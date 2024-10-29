//This file is unchanged from e1client.hpp, just changed names from e1client to just client

#ifndef __CLIENT_HPP_
#define __CLIENT_HPP_
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <atomic>
#include <sys/socket.h>
#include <arpa/inet.h>

#ifdef __APPLE__
#define MSG_CONFIRM 0
#endif

#include "dumpHex.hpp"

#include "network.hpp"

#include "clientStubRPC.hpp" //Except for this

using namespace std;

class client: public Node {

public:
    client(string name): Node(name){}
    ~client(){
        stop();
    }
    void start();
};


#endif