#ifndef PTRNODE_H
#define PTRNODE_H

#include <cstdint>
#include <cstring>

struct tNodeEntry {
    tNodeEntry() {inUse = 0u; ptr = 0;}
    uint8_t inUse;
    void*   ptr;
};

class CPtrNode
{
public:
    CPtrNode(CPtrNode* upNode = 0) {
        up    = upNode;
        if (upNode != 0) {
            layer = upNode->layer-1;
        } else {
            layer = 0;
        }
        full  = 0;
        unused[0] = unused[1] = unused[2] = unused[3] = UINT64_MAX;
        memset(entry, 0, sizeof(entry));
    }
    ~CPtrNode();
    bool isFull() {return full;}
    uint16_t getUnused() {
        uint16_t pos;
        //  if there is a single 1 bit we get the index+1 to it.
        if ((pos=__builtin_ffsl(unused[0]))) {
            return (pos-1);
        } else if ((pos=__builtin_ffsl(unused[1]))) {
            return (63+pos);
        } else if ((pos=__builtin_ffsl(unused[2]))) {
            return (127+pos);
        } else if ((pos=__builtin_ffsl(unused[3]))) {
            return (191+pos);
        } else {
            return (UINT16_MAX);
        }
    }
    CPtrNode* Insert(uint64_t id, void* obj);
    void      Insert(uint8_t* id, void* obj);
    void      Remove(uint64_t id);
    void      Remove(uint8_t* id);
    bool      Release(uint64_t id);
    bool      Release(uint8_t* id);
    void*     Find(uint64_t id);
    void*     Find(uint8_t* id);
    CPtrNode* Allocate(uint64_t& id);
    void      Allocate(uint8_t* id);
public:
    CPtrNode*     up;
    uint8_t       layer;      // layer starts with zero the LSB
    uint8_t       full:1;
    uint64_t      unused[4];  // Bitmap for usage map
    void*         entry[256]; // Node or object;
};

#endif // PTRNODE_H
