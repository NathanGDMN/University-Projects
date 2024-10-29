
#include "network.hpp"
#include "kvservice.hpp"

class KVServer: public Node{
    private:
        shared_ptr<KVServiceServer> kvService;
    public:
        KVServer(string nodeName);
	~KVServer(){
	}

	void start();
    
        void setDBMFileName(string name);
	void setSvcName(string name);
	void setSvcDirServer(string name);
        void setPort(in_port_t p) { kvService->setPort(p);}
        void setPrimary(bool inputBool);
        void addReplica(string replicaName, in_port_t port);
};
