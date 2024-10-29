#include <cstdint>

bool kvPut(int32_t key, const uint8_t * value, uint16_t vlen);
struct kvGetResult{
    bool status;
    uint8_t * value;
    uint16_t vlen;
};
kvGetResult kvGet(int32_t key);

struct messageHeader{
    int magicNumber; //Protocol identifier
    int versionNumber; //Protocol version
    int messageIdentifier;
};