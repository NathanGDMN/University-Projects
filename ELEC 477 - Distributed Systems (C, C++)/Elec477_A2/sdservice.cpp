#include "sdservice.hpp"

using namespace std;
using namespace string_literals;

#define close mclose
void mclose(int fd);

void SDServiceServer::stop(){
    alive = false;
}

void SDServiceServer::start(){
    //cerr << "in kvserviceServer::start" << endl;
    struct sockaddr_in servaddr, cliaddr;
    
    //define C++ map to store values.
    map<string, pair<string, int>> mp;
    
    // get a socket to recieve messges
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        return; // this will exit the service thread and stop the server
    }

    // clear variables before initializing
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Port and Interfact information for binding
    // the socket
    servaddr.sin_family    = AF_INET;        // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;   // whatever interface is available
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (::bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        return; // this will exit the service thread and stop the server
    }

    socklen_t len;
    int n;
    //cerr << "alive = " << alive << endl;
    while(alive){ 
	//cerr << "waiting for call from client" << endl;

        // wait for a mesage from a client
	len = sizeof(cliaddr);  //len is value/result
	n = recvfrom(sockfd, (uint8_t *)udpMessage, MAXMSG, 
		    MSG_WAITALL, ( struct sockaddr *) &cliaddr,
		    &len);
        //cerr << "server received " << n << " bytes." << endl;
	//std::cerr << HexDump{udpMessage,(uint32_t)n} << endl;

    //-----Will need to change:
	E477KV::kvRequest receivedMsg;
	E477KV::kvResponse replyMsg;

	if (!receivedMsg.ParseFromArray(udpMessage,n)){
	    cerr << "Couild not parse message" << endl;
	    // ignore
	}

	//cerr << "message parsed" << endl;

	if ((receivedMsg.magic()) != magic){
            cerr << "service unrecognized message" << endl;
        } else {
	    // start by copying version and serial to reply
	    replyMsg.set_magic(magic);
	    replyMsg.set_version(receivedMsg.version());
	    replyMsg.set_serial(receivedMsg.serial());

	    if ((receivedMsg.version() & 0xFF00)  == version1x){
	       // dispatch version 1.x
	       callMethodVersion1(receivedMsg, replyMsg);
	    } else {
		cerr << "unrecognized version" << endl;
		// For now ignore, message doesn't have a wrong version reply
	    }
	    // at this point in time the reply is complete
	    // send response back
	    uint32_t msglen = replyMsg.ByteSizeLong();
	    // double check size
	    replyMsg.SerializeToArray(udpMessage, msglen);
	    //cerr << "reply message" << HexDump{udpMessage,msglen} ;

	    int servern = sendto(sockfd, udpMessage, msglen,
		    MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
	    //cerr << "server sent " << servern << " bytes" << endl;
	}

    }

    close(sockfd);
}

//-----Not sure if I need:
// void KVServiceServer::callMethodVersion1(E477KV::kvRequest &receivedMsg, E477KV::kvResponse &replyMsg){
//     if (receivedMsg.has_putargs()){
// 	stringstream ss;
// 	ss << "put message requested" << endl;
// 	cerr << ss.str();
        
//         const E477KV::putRequest& preq = receivedMsg.putargs();

//         int key = preq.key();
//         string valueAsStr = preq.value();
        
//         bool putRes = kvPut(key, (uint8_t*)valueAsStr.c_str(), valueAsStr.length());
            
//         cerr << "put result is " << putRes << endl;
// 	E477KV::putResponse *presp = replyMsg.mutable_putres();
// 	presp->set_status(putRes);
//     }
//     if (receivedMsg.has_getargs()){
// 	stringstream ss;
// 	ss << "get message requested" << endl;
// 	cerr << ss.str();
        
//         const E477KV::getRequest& greq = receivedMsg.getargs();

//         int key = greq.key();
        
//         kvGetResult result = kvGet(key);

// 	E477KV::getResponse *gr = replyMsg.mutable_getres();
//         gr->set_status(result.status);
//         gr->set_value(string((char*)result.value,result.vlen));
//     }
// }

bool SDServiceServer::sdput(string serviceName, string servername, int port){
    bool result = false; //Whether or not put was completed

    pair<string, int> putValue (servername, port);
    mp[serviceName] = putValue;

    if (mp[serviceName] == putValue){ //check to make sure value was stored in map correctly
        result = true;
    }
    
    return result;
}


sdGetResult SDServiceServer::sdGet(string serviceName){
    sdGetResult res;

    pair<string, int> getValue = mp[serviceName];

    res.servicename = serviceName;
    res.servername = getValue.first;
    res.port = getValue.second;
    res.status = true;

    return res;
}

bool SDServiceServer::sddelete(string serviceName){
    bool result = false; //Whether or not delete was completed 

    mp.erase(serviceName);

    //Check that service was deleted
    auto it = mp.find(serviceName);
    if (it == mp.end()){
        result == true;
    }

    return result;
}

