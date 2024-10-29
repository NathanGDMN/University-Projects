#ifndef _SDRPC_H_
#define _SDRPC_H_

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

using namespace std;

struct sdGetResult{
    bool status;
    string servicename;
    string servername;
    int * port;
};

#endif