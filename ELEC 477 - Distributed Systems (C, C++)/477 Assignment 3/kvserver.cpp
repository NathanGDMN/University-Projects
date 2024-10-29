
#include "kvserver.hpp"


KVServer::KVServer(string nodeName): Node(nodeName){
            // note this is the same as installng the service software on the server
            // it doesn't run yet until the node is started.

            //cout << "KVServer: Server " << nodeName << " adding key value service" << endl;

	    kvService = make_shared<KVServiceServer>(nodeName,weak_from_this());

            addService(kvService);
        }

void KVServer::start(){
   //cerr << "in KVSERVER start" << endl;
}


void KVServer::setDBMFileName(string name){
    kvService -> setDBMFileName(name);

}

void KVServer::setSvcName(string name){
    kvService -> setServiceName(name);
}
void KVServer::setSvcDirServer(string name){
    kvService -> setServiceDirServer(name);
}

void KVServer::setPrimary(bool inputBool){
    kvService -> setPrimary(inputBool);
}

void KVServer::addReplica(string replicaName, in_port_t port){
    kvService -> addReplica(replicaName, port);
}