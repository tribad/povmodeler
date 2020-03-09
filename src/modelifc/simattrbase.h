#ifndef SIMATTRBASE_H
#define SIMATTRBASE_H

#include <stdint.h>
#include <simobj.h>

enum class eSimAttrType : uint8_t {
    Double    = 0x01,
    Int       = 0x02,
    String    = 0x04,
    Reference = 0x08,
    Invalid   = 0xff
};

class CSimAttrBase
{
public:
    CSimAttrBase();
    CSimAttrBase(eSimAttrType aType, uint64_t aOID, uint64_t aVID) {
        attrtype   = aType;
        objectid   = aOID;
        valueid    = aVID;
    }
protected:
    eSimAttrType attrtype;
    uint64_t objectid;
    uint64_t valueid;
};

#endif // SIMATTRBASE_H
