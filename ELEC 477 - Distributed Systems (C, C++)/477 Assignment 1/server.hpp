//Almost all same as e1.server but with extra function

#include "network.hpp"
#include "service.hpp" //Change to name of service file when created

class server: public Node{

    public:
        server(string nodeName);
        changeGDBMfilename(string fileName);
	~server(){
	}
};