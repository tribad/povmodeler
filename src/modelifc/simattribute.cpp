#include <iostream>
#include <variant.h>
#include "simattribute.h"

CSimAttribute::CSimAttribute()
{

}

CSimAttribute::CSimAttribute(uint64_t aOID, uint64_t aVID, uint64_t aVIdx, const tVariant &value) {
    objectid   = aOID;
    valueid    = aVID;
    valueindex = aVIdx;

     *((tVariant*)(this)) = value;
    switch (value.type) {
    case eDouble:
        attrtype = eSimAttrType::Double;
        break;
    case eInt:
    case eUnsigned:
    case eBoolean:
        attrtype = eSimAttrType::Int;
        break;
    case eString:
        attrtype = eSimAttrType::String;
        break;
    case eObjectRef:
        attrtype = eSimAttrType::Reference;
    case eReference:
    case eNull:
        attrtype = eSimAttrType::Invalid;
        break;
    }
}

CSimAttribute::CSimAttribute(uint64_t aOID, uint64_t aVID, const tVariant &value) {
    objectid   = aOID;
    valueid    = aVID;
    valueindex = 0;

     *((tVariant*)(this)) = value;
    switch (value.type) {
    case eDouble:
        attrtype = eSimAttrType::Double;
        break;
    case eInt:
    case eUnsigned:
    case eBoolean:
        attrtype = eSimAttrType::Int;
        break;
    case eString:
        attrtype = eSimAttrType::String;
        break;
    case eObjectRef:
        attrtype = eSimAttrType::Reference;
    case eReference:
    case eNull:
        attrtype = eSimAttrType::Invalid;
        break;
    }
}

CSimAttribute& CSimAttribute::operator =(uint64_t aValue) {
    if ((uint64_t)(*this) != aValue) {
        *((tVariant*)(this)) = aValue;

        stdb_set((uint8_t)attrtype, objectid, valueid, valueindex, *this);
    }

    return *this;
}

CSimAttribute& CSimAttribute::operator = (double aValue) {
    if ((double)(*this) != aValue) {
        *((tVariant*)(this)) = aValue;

        stdb_set((uint8_t)attrtype, objectid, valueid, valueindex, *this);
    }

    return *this;
}

CSimAttribute& CSimAttribute::operator = (const std::string& aValue) {
    if ((std::string)(*this) != aValue) {
        *((tVariant*)(this)) = aValue.c_str();

        stdb_set((uint8_t)attrtype, objectid, valueid, valueindex, *this);
    }

    return *this;
}

CSimAttribute& CSimAttribute::operator = (tSimObjRef aValue) {
    if (((tSimObjRef)(*this)).id != aValue.id) {
        *((tVariant*)(this)) = aValue;

        stdb_set((uint8_t)attrtype, objectid, valueid, valueindex, *this);
    }

    return *this;
}

CSimAttribute& CSimAttribute::operator = (tVariant aValue) {
    switch (type) {
    case eDouble:
        *this = (double)aValue;
        break;
    case eInt:
    case eUnsigned:
    case eBoolean:
        *this = (uint64_t)aValue;
        break;
    case eObjectRef:
        *this = (tSimObjRef)aValue;
        break;
    case eNull:
        *((tVariant*)(this)) = aValue;
        stdb_set((uint8_t)attrtype, objectid, valueid, valueindex, *this);
        break;
    case eString:
        *this = (std::string)aValue;
        break;
    case eReference:
        break;
    default:
        break;
    }
    return *this;
}
