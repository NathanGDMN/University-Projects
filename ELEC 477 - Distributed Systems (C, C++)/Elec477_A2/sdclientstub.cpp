#include "sdclientstub.hpp"

using namespace std;
using namespace std::string_literals;

#define close mclose
void mclose(int fd);

bool SDServiceStub::sdput(string serviceName, string servername, int port){
    // init if needed
    if (!ready){
        if (!init()) {
            // init returned false, so problem setting up the
            // socket onnection
            return false;
        }
    }

    int n;
    socklen_t len;
    uint32_t blen = MAXMSG;
    uint8_t buffer[MAXMSG];	 // to serialize into
    struct sockaddr_in	 servaddrreply;

    // get the current value of serial for this request.
    uint32_t serial = this->serial++;

    // marshal parameters to send.
    //------Need to change following section
    E477KV::kvRequest msg;
    msg.set_magic(magic);
    msg.set_version(version1x);
    msg.set_serial(serial++);
    E477KV::putRequest * pr = msg.mutable_putargs(); 
    pr -> set_key(key);
    pr -> set_value(std::string((const char*)value, vlen));
    blen = msg.ByteSizeLong();
    if (blen > MAXMSG){
        // too long??
	std::cerr << " *** msg too long" << std::endl;
	// errno = ???
	return false;
    }
    msg.SerializeToArray(buffer, blen);
    //std::cout << HexDump{buffer,blen} << endl;

    // send the message to the server.
    //std::cout << "blen = " << dec << blen << endl;
    n = sendto(sockfd, (const char *)buffer, blen,
		MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    //std::cout << "client sendto n = " << n << endl;

    // wait for the reply

    //-------Need to change following section:
    E477KV::kvResponse putRespMsg;
    bool gotMessage = true;
    do {
        len = sizeof(struct sockaddr_in);
        n = recvfrom(sockfd, (char *)buffer, MAXMSG,
                     MSG_WAITALL, (struct sockaddr *) &servaddrreply, &len);
        
        //std::stringstream ss;
        //ss << "client recieved = " << n << std::endl;
        //std::cout << ss.str();
        
        // check for timeout here..
        if (n==-1) { return false; };
        
        if (!putRespMsg.ParseFromArray(buffer,n)){
            cerr << "Couild not parse message" << endl;
            // wait for another mesage
        } else {
            if (putRespMsg.magic() != 'E477'){
                cerr << "Magic Mismatch" << endl;
                gotMessage = false;
            } else {
                if (msg.version() != putRespMsg.version()){
                    cerr << "Version Mismatch" << endl;
                    gotMessage = false;
                } else {
                    // wait for another message is the serial number is wrong.
                    if (msg.serial() != putRespMsg.serial()){
                        cerr << "Serial Numnbers Mismatch" << endl;
                        gotMessage = false;
                    }
                }
            }
        }
    } while (!gotMessage);
    
    bool returnRes = false;
    if (putRespMsg.has_putres()){
      returnRes = putRespMsg.putres().status();
    } else {
      cerr << "wrong message type" << endl;
	returnRes  = false;
    }

    return returnRes;
}

sdGetResult SDServiceStub::sdget(string serviceName){
    // init if needed
    sdGetResult retVal;
    retVal.status=false;
    retVal.value = nullptr;
    retVal.vlen = 0;
    if (!ready){
        if (!init()) {
            // init returned false, so problem setting up the
            // socket onnection
            return retVal;
        }
    }

    struct sockaddr_in	 servaddrreply;

    int n;
    socklen_t len;
    uint32_t blen = MAXMSG;
    uint8_t buffer[MAXMSG];
    E477KV::kvRequest msg;
    msg.set_magic(magic);
    msg.set_version(version1x);
    msg.set_serial(serial++);

    //------Need to change following section
    E477KV::getRequest * gr = msg.mutable_getargs();

    gr -> set_key(key);
    blen = msg.ByteSizeLong();
    if (blen > MAXMSG){
        // too long??
	std::cerr << " *** msg too long" << std::endl;
	// errno = ???
	retVal.status = false;
	return retVal;
    }
    msg.SerializeToArray(buffer, blen);
    //std::cout << HexDump{buffer,blen} << endl;

    // send the message3
    //std::cout << "blen = " << dec << blen << endl;
    n = sendto(sockfd, (const char *)buffer, blen,
		MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    //std::cout << "client sendto n = " << n << endl;

    //-----Need to change following section
    E477KV::kvResponse getRespMsg;
    bool gotMessage = true;
    do {
        len = sizeof(struct sockaddr_in);
        n = recvfrom(sockfd, (char *)buffer, MAXMSG,
                     MSG_WAITALL, (struct sockaddr *) &servaddrreply, &len);
        
        //std::stringstream ss;
        //ss << "client recieved = " << n << std::endl;
        //std::cout << ss.str();
        //std::cout << HexDump{buffer,(uint32_t)n} << endl;
        // check for timeout here..
        if (n==-1) { return retVal; }// null ptrs and falls status };
        
        if (!getRespMsg.ParseFromArray(buffer,n)){
            cerr << "Couild not parse message" << endl;
            // wait for another mesage
        } else {
            if (getRespMsg.magic() != magic){
                gotMessage = false;
            } else {
                if (msg.version() != getRespMsg.version()){
                    cerr << "Version Mismatch" << endl;
                    gotMessage = false;
                } else {
                    // wait for another message is the serial number is wrong.
                    if (msg.serial() != getRespMsg.serial()){
                        cerr << "Serial Numnbers Mismatch" << endl;
                        gotMessage = false;
                    }
                }
            }
        }
    } while(!gotMessage);
    
    if (getRespMsg.has_getres()){
        retVal.status = getRespMsg.getres().status();
        //-----The following are probably wrong
        retVal.servicename = getRespMsg.getres().value().servicename();
        retVal.servername = getRespMsg.getres().value().servername();
        retVal.port = getRespMsg.getres().value().port();

        // ------Need to perform something like the following above
        // new uint8_t[retVal.vlen];
        // memcpy(retVal.value,(uint8_t*)getRespMsg.getres().value().data(), retVal.vlen);
      
    } else {
      cerr << "wrong message type" << endl;
	retVal.status=false;
    }
    //cout << "leaving get stub" << endl;
    return retVal;
}

bool SDServiceStub::sddelete(string serviceName){
    // init if needed
    if (!ready){
        if (!init()) {
            // init returned false, so problem setting up the
            // socket onnection
            return false;
        }
    }

    int n;
    socklen_t len;
    uint32_t blen = MAXMSG;
    uint8_t buffer[MAXMSG];	 // to serialize into
    struct sockaddr_in	 servaddrreply;

    // get the current value of serial for this request.
    uint32_t serial = this->serial++;

    // marshal parameters to send.
    //-----Need to change following section
    E477KV::kvRequest msg;
    msg.set_magic(magic);
    msg.set_version(version1x);
    msg.set_serial(serial++);
    E477KV::putRequest * pr = msg.mutable_putargs(); 
    pr -> set_key(key);
    pr -> set_value(std::string((const char*)value, vlen));
    blen = msg.ByteSizeLong();
    if (blen > MAXMSG){
        // too long??
	std::cerr << " *** msg too long" << std::endl;
	// errno = ???
	return false;
    }
    msg.SerializeToArray(buffer, blen);
    //std::cout << HexDump{buffer,blen} << endl;

    // send the message to the server.
    //std::cout << "blen = " << dec << blen << endl;
    n = sendto(sockfd, (const char *)buffer, blen,
		MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    //std::cout << "client sendto n = " << n << endl;

    // wait for the reply

    //-------Need to change following section:
    E477KV::kvResponse putRespMsg;
    bool gotMessage = true;
    do {
        len = sizeof(struct sockaddr_in);
        n = recvfrom(sockfd, (char *)buffer, MAXMSG,
                     MSG_WAITALL, (struct sockaddr *) &servaddrreply, &len);
        
        //std::stringstream ss;
        //ss << "client recieved = " << n << std::endl;
        //std::cout << ss.str();
        
        // check for timeout here..
        if (n==-1) { return false; };
        
        if (!putRespMsg.ParseFromArray(buffer,n)){
            cerr << "Couild not parse message" << endl;
            // wait for another mesage
        } else {
            if (putRespMsg.magic() != 'E477'){
                cerr << "Magic Mismatch" << endl;
                gotMessage = false;
            } else {
                if (msg.version() != putRespMsg.version()){
                    cerr << "Version Mismatch" << endl;
                    gotMessage = false;
                } else {
                    // wait for another message is the serial number is wrong.
                    if (msg.serial() != putRespMsg.serial()){
                        cerr << "Serial Numnbers Mismatch" << endl;
                        gotMessage = false;
                    }
                }
            }
        }
    } while (!gotMessage);
    
    bool returnRes = false;
    if (putRespMsg.has_putres()){
      returnRes = putRespMsg.putres().status();
    } else {
      cerr << "wrong message type" << endl;
	returnRes  = false;
    }

    return returnRes;
}

// set up socket for calls to server
bool SDServiceStub::init(){

    if (serverName.empty()){
        cerr << "Does not know server name!! " << endl;
        return false;
    }

    // Filling server information
    // TODO - need to add service lookup concept
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);

    // look up address by name (Version 2 of network.cpp)
    struct addrinfo * res;
    int numAddr = getaddrinfo(serverName.c_str(), nullptr, nullptr, &res);
    //cerr << "number of address results is " << numAddr << endl;
    servaddr.sin_addr = ((struct sockaddr_in*)res -> ai_addr) -> sin_addr;
    freeaddrinfo(res);
    
    // old version that used address directly
    //inet_aton(serverAddrString.c_str(), &servaddr.sin_addr);


    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
	perror("socket creation failed");
        return false;
    }

    // set socket to timeout in 1 second if reply not received
    // TODO this should be a parameter somehwere.
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv,sizeof(tv)) < 0) {
        perror("Error");
        return false;
    }
    ready = true;
    return true;

}

void SDServiceStub::shutdown(){
    if (!ready) return;
    close(sockfd);
    ready = false;
}

