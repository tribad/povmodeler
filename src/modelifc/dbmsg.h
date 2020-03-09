// **************************************************************************
//
//  Modul-Name     : dbmsg.h
//  Author(s)      : Hans-Juergen Lange
//
//  Copyrights 2014 by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
#ifndef DBMSG_H
#define DBMSG_H

#include <msg.h>
#include <msgdb.h>
#include <variant.h>

typedef enum enumDBMsgIds {
    eMsgDBTransactionStart=0x0f00,
    eMsgDBTransactionEnd,
    eMsgDBDeleteObject,
    eMsgDBCreateObject,
    eMsgDBCreateFromTemplate,
    eMsgDBValueDouble,
    eMsgDBValueU64,
    eMsgDBValueI64,
    eMsgDBValueString,
    eMsgDBValueReference,
    eMsgDBSet
} eDBMsgIds;

typedef enum enumValueAction {
    eValueCreate,
    eValueDelete,
    eValueUpdate
} eValueAction;

/*
 * Here are some messages used with the TLog mechanism.
 * Some of them are still used to update the Simulation DB
 */
struct tMsgDBTransactionStart : public tMsgDB {
    tMsgDBTransactionStart() {id = eMsgDBTransactionStart; }
    virtual ~tMsgDBTransactionStart();
};

struct tMsgDBTransactionEnd : public tMsgDB {
    tMsgDBTransactionEnd() {id = eMsgDBTransactionEnd;}
    virtual ~tMsgDBTransactionEnd();
};

struct tMsgDBValue : public tMsgDB {
    tMsgDBValue() {}
    virtual ~tMsgDBValue() {
        if (id == eMsgDBValueString) {
            if (value.str != nullptr) {
                //
                //  As this message gets send from the simapi it has been allocated
                //  through strdup() that uses malloc. So we have to use free here.
                free(value.str);
            }
        }
    }
    uint64_t   objid;             //  The Object ID
    uint64_t    valueid;           //  Value ID
    uint64_t index;             //  The index on array values.
    eValueAction action;        //  What todo. Create/Delete/Update
    union {
        double dbl;
        uint64_t u64;
        int64_t  i64;
        char *str;
    } value;
};

struct tMsgDBDeleteObject : public tMsgDB {
    tMsgDBDeleteObject() {}
    virtual ~tMsgDBDeleteObject() {}
    uint64_t objectid;
};

struct tMsgDBCreateObject : public tMsgDB {
    tMsgDBCreateObject() {}
    virtual ~tMsgDBCreateObject() {}
    uint64_t   objectid;
    uint64_t   type;
} ;

struct tMsgDBCreateFromTemplate : public tMsgDB {
    tMsgDBCreateFromTemplate() {}
    virtual ~tMsgDBCreateFromTemplate() {}
    uint64_t templateid;
    uint64_t objectid;
    uint64_t type;
};

struct tMsgDBSet : tMsgDB {
    tMsgDBSet() {id = eMsgDBSet;}
    tMsgDBSet(uint8_t aAttrType, uint64_t aOID, uint64_t aVID, uint64_t aVIDX, const tVariant& aValue) {
        attrtype = aAttrType; oid = aOID; vid = aVID; vidx = aVIDX; value = aValue; id = eMsgDBSet;
    }
    virtual ~tMsgDBSet() {}
    uint8_t  attrtype;
    uint64_t oid;
    uint64_t vid;
    uint64_t vidx;
    tVariant value;
};

#endif // DBMSG_H
