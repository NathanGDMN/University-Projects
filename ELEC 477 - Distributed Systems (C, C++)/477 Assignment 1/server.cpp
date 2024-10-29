#include "server.hpp"

server::server(string nodeName): Node(nodeName){
    // note this is the same as installng the service software on the server
    // it doesn't run yet until the node is started.

    cout << "Main: Server " << nodeName << " adding example 1 service" << endl;

    shared_ptr<Service> service = make_shared<E1ServiceServer>(nodeName,weak_from_this());
    addService(service);
}

server::changeGDBMfilename(string fileName){
    Service.changeGDBMfilename(fileName) //Need to create server instance just to do this
}