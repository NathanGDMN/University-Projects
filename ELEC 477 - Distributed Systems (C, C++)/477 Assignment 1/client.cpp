#include "client.hpp"

using namespace std;
using namespace std::string_literals;

clientStub stub;

void client::start(){
    //Parameters of kvPut() and kvGet()
    int32_t key; 
    const uint8_t * value; 
    uint16_t vlen;

    stub.setServerAddress("10.0.0.2") //Address from e1client.cpp

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    stub.kvPut(key, value, vlen);

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    stub.kvGet(key);

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    stub.shutdownServer();

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

}