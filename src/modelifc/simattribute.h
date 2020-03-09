#ifndef SIMATTRIBUTE_H
#define SIMATTRIBUTE_H

#include <stdint.h>
#include <simobj.h>
#include <simattrbase.h>

tSimObj* simfindidx(uint64_t aValue);
void stdb_set(objectid_t objid, valueid_t valueid, valueindex_t index, double value);
void stdb_set(objectid_t objid, valueid_t valueid, valueindex_t index, int64_t value);
void stdb_set(objectid_t objid, valueid_t valueid, valueindex_t index, const std::string& value);
void stdb_set(objectid_t objid, valueid_t valueid, valueindex_t index, tSimObjRef value);
void stdb_set(uint8_t attrtype, objectid_t objid, valueid_t valueid, valueindex_t index, const tVariant&);
void stdb_del(uint8_t attrtype, objectid_t objid, valueid_t valueid, valueindex_t index);

class CSimAttribute : public CSimAttrBase, public tVariant
{
public:
    CSimAttribute();
    CSimAttribute(eSimAttrType aType, uint64_t aOID, uint64_t aVID, uint64_t aVIdx) : CSimAttrBase(aType, aOID, aVID) {
        valueindex = aVIdx;
    }
    CSimAttribute(uint64_t aOID, uint64_t aVID, uint64_t aVIdx, const tVariant& value);
    CSimAttribute(uint64_t aOID, uint64_t aVID, const tVariant& value);
    CSimAttribute& operator=(uint64_t value);
    CSimAttribute& operator=(double value);
    CSimAttribute& operator=(int64_t value);
    CSimAttribute& operator=(tSimObj* value);
    CSimAttribute& operator=(tSimObjRef value);
    CSimAttribute& operator=(tVariant value);
    CSimAttribute& operator=(const std::string & value);
private:
    uint64_t valueindex;
};

#endif // SIMATTRIBUTE_H
