#ifndef SDSERVER_HPP
#define SDSERVER_HPP

#include "network.hpp"
#include "sdservice.hpp"

class SDServer: public Node{
    private:
        shared_ptr<KVServiceServer> kvService;
    public:
        SDServer(string nodeName);
	~SDServer(){
	}

	void start();
    
};

#endif
