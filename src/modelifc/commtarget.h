#ifndef COMMTARGET_H
#define COMMTARGET_H

#include <stdint.h>

class CMsgQueue;

enum class eCommTarget {
    Connection,
    Object,
    Node,
    DB,
    Queue,
    Unknown
};

enum class eCommFormat {
    JSON,
    Binary,
    Raw,
    Unknown
};

typedef struct tagConnection {
    uint64_t    id;
    eCommFormat format;
} tConnection;

typedef struct tagObject {
    uint64_t id;
    void*    ptr;
} tObject;

typedef struct tagNode {
    uint64_t nodeid;
} tNode;

struct tQueue {
    void* ptr;
    CMsgQueue* operator->() {return static_cast<CMsgQueue*>(ptr);}
};

struct tCommTarget {
    tCommTarget() {type = eCommTarget::Unknown;}
    tCommTarget(uint64_t aId, void* aPtr) {type = eCommTarget::Object; obj.id = aId; obj.ptr = aPtr;}
    eCommTarget type;
    union {
        tConnection conn;
        tObject     obj;
        tNode       node;
        tQueue      queue;
    };
    static tCommTarget mainobj;
};


#endif
