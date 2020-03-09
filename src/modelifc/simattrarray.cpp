#include "simattrarray.h"


CSimAttrArray::CSimAttrArray(uint64_t aOID, uint64_t aVID, eSimAttrType aType, bool aShared) {
    objectid = aOID;
    valueid  = aVID;
    attrtype = aType;
    shared   = aShared;
}

CSimAttrArray::CSimAttrArray(bool aShared)
{
    shared = aShared;
}

CSimAttribute& CSimAttrArray::operator [](uint64_t aIndex) {
    tSimAttrArrayIter ai = array.find(aIndex);

    if (ai == array.end()) {
        array.insert(std::pair<uint64_t, CSimAttribute>(aIndex, CSimAttribute(attrtype, objectid, valueid, aIndex)));
    }
    return array[aIndex];
}

void CSimAttrArray::erase(uint64_t key) {
    tSimAttrArrayIter ai = array.find(key);

    if (ai != array.end()) {
        stdb_del((uint8_t)attrtype, objectid, valueid, key);
        array.erase(key);
    }
}
