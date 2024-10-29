#include "clientStubRPC.hpp"    

//Was previously in client (e1client.cpp)
using namespace std;
using namespace std::string_literals;

#define close mclose

const int MAXMSG = 1400;
in_port_t PORT = 8080;

//Was previously in e1client.cpp start() at top:
int n;
int sockfd; //Current socket "file descriptor"
socklen_t len;
uint32_t blen = MAXMSG;
uint8_t buffer[MAXMSG];	 // to serialize into
struct sockaddr_in servaddr;

//Stuff to be included in meassage headers:
const string RPCIdentifier = "HelloRPC";
const int RPCVersion = 1;
int messageId; //Dependent of what command you are giving it

bool clientStub::kvPut(int32_t key, const uint8_t * value, uint16_t vlen){
    messageId = 1;

    string message = RPCIdentifier + to_string(RPCVersion) + to_string(messageId) + "Client request to store"

    protoMsg = ; //message = result from protobuff

    //Send message to serevr
    blen = snprintf((char*)buffer, MAXMSG, protoMsg)+1;
    n = sendto(sockfd, (const char *)buffer, blen, MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    std::cout << "client sendto n = " << n << endl;

    //Wait for response
    len = sizeof(struct sockaddr_in);
    n = recvfrom(sockfd, (char *)buffer, MAXMSG, MSG_WAITALL, (struct sockaddr *) &servaddrreply, &len);
    if (n==-1) {
        //If timeout
        if (errno == EWOULDBLOCK){
	    std::cout << "client timed out" << std::endl;
        } else {
            perror("recvfrom");
        }
    } else {
        //What to do with response
        std::cout << "client recieved = " << n << std::endl;
	    std::cout << HexDump{buffer,(uint32_t)n} << endl;

        /* Use protobuff to unmarshall/decode
            -Reture true or false based on response
        */
    }
}


kvGetResult clientStub::kvGet(int32_t key){
    messageId = 2;
    kvGetResult result; //What will be returned at end

    string message = RPCIdentifier + to_string(RPCVersion) + to_string(messageId) + "Client request to store"

    protoMsg = ; //message = result from protobuff

    //Send message to serevr
    blen = snprintf((char*)buffer, MAXMSG, protoMsg)+1;
    n = sendto(sockfd, (const char *)buffer, blen, MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    std::cout << "client sendto n = " << n << endl;

    //Wait for response
    len = sizeof(struct sockaddr_in);
    n = recvfrom(sockfd, (char *)buffer, MAXMSG, MSG_WAITALL, (struct sockaddr *) &servaddrreply, &len);
    if (n==-1) {
        //If timeout
        if (errno == EWOULDBLOCK){
	    std::cout << "client timed out" << std::endl;
        } else {
            perror("recvfrom");
        }
    } else {
        //What to do with response
        std::cout << "client recieved = " << n << std::endl;
	    std::cout << HexDump{buffer,(uint32_t)n} << endl;
        /* Use protobuff to unmarshall/decode
            -fill out kvGetResult struct:
        */
       kvGetResult result;
       result.value = ;
       result.vlen = ;
       result.status = ;
    }
    return result;
}


bool clientStub::setServerAddress(string addr){
    // Server information
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    
    if (currentServer != ""){ //If this block causes error just remove it. You'll just have to make sure to use shutdown function before this one
        close(sockfd);
    }
    
    inet_aton(addr, &servaddr.sin_addr);

    // Open a socket to send the info.
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
	    perror("socket creation failed");
	    exit(EXIT_FAILURE);
    }

    // set socket to timeout in 1 second if reply not received
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv,sizeof(tv)) < 0) {
        perror("setsockopt");
        exit(1);
    }

    return true;
}

bool clientStub::shutdownServer(){
    close(sockfd);
}