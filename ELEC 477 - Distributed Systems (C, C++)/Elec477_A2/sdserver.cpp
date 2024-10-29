#include "sdserver.hpp"


KVServer::SDServer(string nodeName): Node(nodeName){
            // note this is the same as installng the service software on the server
            // it doesn't run yet until the node is started.

            //cout << "Main: Server " << nodeName << " adding key value service" << endl;

	    sdService = make_shared<KVServiceServer>(nodeName,weak_from_this());

            addService(sdService);
        }

void SDServer::start(){
   //cerr << "in KVSERVER start" << endl;
}
