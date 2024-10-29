#include <map>

#include "keyValueRPC.hpp"

using namespace std;

struct storedValue{
    uint8_t value;
    uint16_t vlen;
};

map<int32_t, storedValue> mp;

//kvPut:
bool kvPut(int32_t key, const uint8_t * value, uint16_t vlen){
    mp[key] = {*value, vlen};
    
    if (mp[key].value == *value){
        return true;
    }else{
        return false;
    }
}

//kvGetResult:
kvGetResult kvGet(int32_t key){
    kvGetResult result;

    if(mp.find(key) == mp.end()){ //If no value at key
        result.status = false;
    }else{
        result.value = &mp[key].value;
        result.vlen = mp[key].vlen;
        result.status = true;
    }

    return result;
}