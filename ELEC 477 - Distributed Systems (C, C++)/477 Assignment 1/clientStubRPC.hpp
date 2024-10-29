#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>

#ifdef __APPLE__
#define MSG_CONFIRM 0
#endif

//Stuff I included:

#include <string>



class clientStub {

    /* Needs to include:
        -Invocation of kvPut(), kvGet() on server
        -Method for setting/changing server address
        -Shutdown method
    */
   
    private:
    currentServer = ""; //Address of current server connected through socket

    public:
    bool kvPut(int32_t key, const uint8_t * value, uint16_t vlen);
    
    struct kvGetResult{
        bool status;
        uint8_t * value;
        uint16_t vlen;
    };
    kvGetResult kvGet(int32_t key);

    bool setServerAddress(string addr); //Sets server addr and create connection

    bool shutdownServer();

};