#include <simapi.h>
#include <dbmsg.h>
#include <coreifc.h>
#include <tSigSQLExecStringReq.h>
#include <tSigSQLConnectReq.h>
#include <tSigSQLDisconnectReq.h>
#include <tSigSQLFetchReq.h>
#include <msgqueue.h>

extern CCoreIfc* __coreIfc;

void ScheduleSignal(tSig *sig) {
    __coreIfc->ScheduleSignal(sig);
}

void ScheduleMsg(tMsg *msg) {
    __coreIfc->ScheduleMsg(msg);
}

void StartObject(tSimObj *obj) {
    __coreIfc->StartObject(obj);
}

void FreeObject(tSimObj *obj) {
    __coreIfc->FreeObject(obj);
}

void SetCycle(uint64_t aCycle) {
    __coreIfc->absCycle = aCycle;
}

uint64_t GetCycle() {
    return (__coreIfc->absCycle);
}


void DeleteObject(tSimObj* obj) {
    obj->update = 0;
    //
    //  In between we must free the index as well.
    FreeObject(obj);
}

tMsg* SendMsg(const tSimAttrArrayIter &iter, tMsg* msg) {
    tSimObjRef ref = iter->second;
    tMsg*      retval = 0;

    if (ref.ptr != 0) {
        tSimObj* obj = (tSimObj*)ref.ptr;
        retval = obj->syncprocess(obj, msg);
    }
    return retval;
}

void SendSig(const tSimAttrArrayIter &iter, tSig* sig) {
    tSimObjRef ref = iter->second;

    if (ref.ptr != 0) {
        tSimObj* obj = (tSimObj*)ref.ptr;

        obj->process(obj, sig);
    }
}

tMsg* SendMsg(const tSimObjRef &ref, tMsg* msg) {
    tMsg*      retval = 0;

    if (ref.ptr != 0) {
        tSimObj* obj = (tSimObj*)ref.ptr;
        retval = obj->syncprocess(obj, msg);
    }
    return retval;
}

tMsg* SendMsg(tMsg* msg) {
    tMsg* retval = 0;

    switch (msg->dst.type) {
    case eCommTarget::Connection:
        __coreIfc->comm->Put(msg);
        break;
    case eCommTarget::DB:
        __coreIfc->stdb->Put(msg);
        break;
    case eCommTarget::Object:
        if (msg->dst.obj.ptr == 0) {
            __coreIfc->comm->Put(msg);
        } else {
            retval = SendMsg((tSimObj*)(msg->dst.obj.ptr), msg);
        }
        break;
    default:
        __coreIfc->comm->Put(msg);
        break;
    }
    return retval;
}

void SendSig(const tSimObjRef &ref, tSig* sig) {
    if (ref.ptr != 0) {
        tSimObj* obj = (tSimObj*)ref.ptr;

        obj->process(obj, sig);
    }
}

tMsg* SendMsg(const tSimObjRefIter &iter, tMsg* msg) {
    tSimObjRef ref = iter->second;
    tMsg*      retval = 0;

    if (ref.ptr != 0) {
        tSimObj* obj = (tSimObj*)ref.ptr;
        retval = obj->syncprocess(obj, msg);
    }
    return retval;
}

void SendSig(const tSimObjRefIter &iter, tSig* sig) {
    tSimObjRef ref = iter->second;

    if (ref.ptr != 0) {
        tSimObj* obj = (tSimObj*)ref.ptr;

        obj->process(obj, sig);
    }
}
tMsg* SendMsg(tSimObj* ptr, tMsg* msg) {
    tMsg*      retval = 0;

    if (ptr != 0) {
        retval = ptr->syncprocess(ptr, msg);
    }
    return retval;
}

void SendSig(tSimObj* ptr, tSig* sig) {

    if (ptr != 0) {
        ptr->process(ptr, sig);
    }
}


void SendSig(tSig* sig) {
    switch (sig->dst.type) {
    case eCommTarget::Connection:
        __coreIfc->comm->Put(sig);
        break;
    case eCommTarget::DB:
        __coreIfc->stdb->Put(sig);
        break;
    case eCommTarget::Object:
        if (sig->dst.obj.ptr == 0) {
            __coreIfc->comm->Put(sig);
        } else {
            SendSig((tSimObj*)(sig->dst.obj.ptr), sig);
        }
        break;
    default:
        __coreIfc->comm->Put(sig);
        break;
    }
}

tMsg* SendMsgToParent(const tSimAttrArrayIter &iter, tMsg* msg) {
    tSimObjRef ref    = iter->second;
    tMsg*      retval = 0;

    if (ref.ptr != 0) {
        tSimObj* obj    = (tSimObj*)ref.ptr;
        tSimObj* parent = obj->parent;

        if (parent != 0) {
            retval = parent->syncprocess(parent, msg);
        }
    }
    return retval;
}

void SendSigToParent(const tSimAttrArrayIter &iter, tSig* sig) {
    tSimObjRef ref = iter->second;

    if (ref.ptr != 0) {
        tSimObj* obj    = (tSimObj*)ref.ptr;
        tSimObj* parent = obj->parent;

        if (parent != 0) {
            parent->process(parent, sig);
        }
    }
}

tMsg* SendMsgToParent(const tSimObjRef &ref, tMsg* msg) {
    tMsg*      retval = 0;

    if (ref.ptr != 0) {
        tSimObj* obj    = (tSimObj*)ref.ptr;
        tSimObj* parent = obj->parent;

        if (parent != 0) {
            retval = parent->syncprocess(parent, msg);
        }
    }
    return retval;
}

void SendSigToParent(const tSimObjRef &ref, tSig* sig) {
    if (ref.ptr != 0) {
        tSimObj* obj    = (tSimObj*)ref.ptr;
        tSimObj* parent = obj->parent;

        if (parent != 0) {
            parent->process(parent, sig);
        }
    }
}

tMsg* SendMsgToParent(const tSimObjRefIter &iter, tMsg* msg) {
    tSimObjRef ref = iter->second;
    tMsg*      retval = 0;

    if (ref.ptr != 0) {
        tSimObj* obj    = (tSimObj*)ref.ptr;
        tSimObj* parent = obj->parent;

        if (parent != 0) {
            retval = parent->syncprocess(parent, msg);
        }
    }
    return retval;
}

void SendSigToParent(const tSimObjRefIter &iter, tSig* sig) {
    tSimObjRef ref = iter->second;

    if (ref.ptr != 0) {
        tSimObj* obj    = (tSimObj*)ref.ptr;
        tSimObj* parent = obj->parent;

        if (parent != 0) {
            parent->process(parent, sig);
        }
    }
}

tSimObj* GetParent(const tSimAttrArrayIter &iter) {
    tSimObj*   retval = 0;
    tSimObjRef ref    = iter->second;

    if (ref.ptr != 0) {
        tSimObj* obj    = (tSimObj*)ref.ptr;

        retval = obj->parent;
    }
    return retval;
}


tSimObj* GetParent(const tSimObjRef &ref) {
    tSimObj*   retval = 0;

    if (ref.ptr != 0) {
        tSimObj* obj    = (tSimObj*)ref.ptr;

        retval = obj->parent;
    }
    return retval;
}

tSimObj* GetParent(const tSimObjRefIter &iter) {
    tSimObj*   retval = 0;
    tSimObjRef ref = iter->second;

    if (ref.ptr != 0) {
        tSimObj* obj    = (tSimObj*)ref.ptr;

        retval = obj->parent;
    }
    return retval;
}

tVariant GetValue(const tSimObjRefIter &iter, uint64_t vid, uint64_t vidx) {
    tVariant retval;
    tSimObjRef ref = iter->second;
    tSimObj*   obj = (tSimObj*)(ref.ptr);

    if (obj != 0) {
        retval = obj->getvalue(obj, vid, vidx);
    }
    return retval;
}

tVariant GetValue(const tSimObjRefIter &iter, uint64_t vid) {
    tVariant retval;
    tSimObjRef ref = iter->second;
    tSimObj*   obj = (tSimObj*)(ref.ptr);

    if (obj != 0) {
        retval = obj->getvalue(obj, vid, 0);
    }
    return retval;
}

void SetValue(const tSimObjRefIter &iter, uint64_t vid, uint64_t vidx, const tVariant &value) {
    tSimObjRef ref = iter->second;
    tSimObj*   obj = (tSimObj*)(ref.ptr);

    if (obj != 0) {
        obj->setvalue(obj, vid, vidx, value);
    }
}

void SetValue(const tSimObjRefIter &iter, uint64_t vid, const tVariant &value) {
    tSimObjRef ref = iter->second;
    tSimObj*   obj = (tSimObj*)(ref.ptr);

    if (obj != 0) {
        obj->setvalue(obj, vid, 0, value);
    }
}

tVariant GetValue(const tSimAttrArrayIter &iter, uint64_t vid, uint64_t vidx) {
    tVariant retval;
    tSimObjRef ref = iter->second;
    tSimObj*   obj = (tSimObj*)(ref.ptr);

    if (obj != 0) {
        retval = obj->getvalue(obj, vid, vidx);
    }
    return retval;
}

tVariant GetValue(const tSimAttrArrayIter &iter, uint64_t vid) {
    tVariant retval;
    tSimObjRef ref = iter->second;
    tSimObj*   obj = (tSimObj*)(ref.ptr);

    if (obj != 0) {
        retval = obj->getvalue(obj, vid, 0);
    }
    return retval;
}

void SetValue(const tSimAttrArrayIter &iter, uint64_t vid, uint64_t vidx, const tVariant &value) {
    tSimObjRef ref = iter->second;
    tSimObj*   obj = (tSimObj*)(ref.ptr);

    if (obj != 0) {
        obj->setvalue(obj, vid, vidx, value);
    }
}

void SetValue(const tSimAttrArrayIter &iter, uint64_t vid, const tVariant &value) {
    tSimObjRef ref = iter->second;
    tSimObj*   obj = (tSimObj*)(ref.ptr);

    if (obj != 0) {
        obj->setvalue(obj, vid, 0, value);
    }
}



tVariant GetValue(const tSimObjRef &ref, uint64_t vid, uint64_t vidx) {
    tVariant retval;
    tSimObj*   obj = (tSimObj*)(ref.ptr);

    if (obj != 0) {
        retval = obj->getvalue(obj, vid, vidx);
    }
    return retval;
}

tVariant GetValue(const tSimObjRef &ref, uint64_t vid) {
    tVariant retval;
    tSimObj*   obj = (tSimObj*)(ref.ptr);

    if (obj != 0) {
        retval = obj->getvalue(obj, vid, 0);
    }
    return retval;
}

void SetValue(const tSimObjRef &ref, uint64_t vid, uint64_t vidx, const tVariant &value) {
    tSimObj*   obj = (tSimObj*)(ref.ptr);

    if (obj != 0) {
        obj->setvalue(obj, vid, vidx, value);
    }
}

void SetValue(const tSimObjRef &ref, uint64_t vid, const tVariant &value) {
    tSimObj*   obj = (tSimObj*)(ref.ptr);

    if (obj != 0) {
        obj->setvalue(obj, vid, 0, value);
    }
}

tVariant GetValue(tSimObj* obj, uint64_t vid, uint64_t vidx) {
    tVariant retval;

    if (obj != 0) {
        retval = obj->getvalue(obj, vid, vidx);
    }
    return retval;
}

tVariant GetValue(tSimObj* obj, uint64_t vid) {
    tVariant retval;

    if (obj != 0) {
        retval = obj->getvalue(obj, vid, 0);
    }
    return retval;
}

void SetValue(tSimObj* obj, uint64_t vid, uint64_t vidx, const tVariant &value) {
    if (obj != 0) {
        obj->setvalue(obj, vid, vidx, value);
    }
}

void SetValue(tSimObj* obj, uint64_t vid, const tVariant &value) {
    if (obj != 0) {
        obj->setvalue(obj, vid, 0, value);
    }
}


void stdb_createobj(objectid_t objid, typeid_t type) {

    if (__coreIfc->stdb != 0) {
        tMsgDBCreateObject *msg=new tMsgDBCreateObject;

        msg->id=eMsgDBCreateObject;
        msg->objectid=objid;
        msg->type=type;
        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_createfromtemplate(templateid_t templateid, objectid_t objid, typeid_t type) {

    if (__coreIfc->stdb != 0) {
        tMsgDBCreateFromTemplate *msg = new tMsgDBCreateFromTemplate;

        msg->id=eMsgDBCreateFromTemplate;
        msg->templateid=templateid;
        msg->objectid=objid;
        msg->type=type;
        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_deleteobj(objectid_t objid) {

    if (__coreIfc->stdb != 0) {
        tMsgDBDeleteObject *msg = new tMsgDBDeleteObject;

        msg->id=eMsgDBDeleteObject;
        msg->objectid=objid;
        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_createdata(objectid_t objid, valueid_t valueid, valueindex_t index, double value) {

    if (__coreIfc->stdb != 0) {
        tMsgDBValue *msg = new tMsgDBValue;

        msg->id=eMsgDBValueDouble;
        msg->objid=objid;
        msg->valueid=valueid;
        msg->index=index;
        msg->action=eValueCreate;
        msg->value.dbl=value;
        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_updatedata(objectid_t objid, valueid_t valueid, valueindex_t index, double value) {

    if (__coreIfc->stdb != 0) {
        tMsgDBValue *msg = new tMsgDBValue;

        msg->id=eMsgDBValueDouble;
        msg->objid=objid;
        msg->valueid=valueid;
        msg->index=index;
        msg->action=eValueUpdate;
        msg->value.dbl=value;
        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_deletefloatdata(objectid_t objid, valueid_t valueid, valueindex_t index) {

    if (__coreIfc->stdb != 0) {
        tMsgDBValue *msg = new tMsgDBValue;

        msg->id=eMsgDBValueDouble;
        msg->objid=objid;
        msg->valueid=valueid;
        msg->index=index;
        msg->action=eValueDelete;
        msg->value.dbl=0;
        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_createdata(objectid_t objid, valueid_t valueid, valueindex_t index, uint64_t value) {

    if (__coreIfc->stdb != 0) {
        tMsgDBValue *msg = new tMsgDBValue;

        msg->id=eMsgDBValueU64;
        msg->objid=objid;
        msg->valueid=valueid;
        msg->index=index;
        msg->action=eValueCreate;
        msg->value.u64=value;
        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_updatedata(objectid_t objid, valueid_t valueid, valueindex_t index, uint64_t value) {

    if (__coreIfc->stdb != 0) {
        tMsgDBValue *msg = new tMsgDBValue;

        msg->id=eMsgDBValueU64;
        msg->objid=objid;
        msg->valueid=valueid;
        msg->index=index;
        msg->action=eValueUpdate;
        msg->value.u64=value;
        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_createdata(objectid_t objid, valueid_t valueid, valueindex_t index, bool value) {

    if (__coreIfc->stdb != 0) {
        tMsgDBValue *msg = new tMsgDBValue;

        msg->id=eMsgDBValueU64;
        msg->objid=objid;
        msg->valueid=valueid;
        msg->index=index;
        msg->action=eValueCreate;
        msg->value.u64=value;
        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_updatedata(objectid_t objid, valueid_t valueid, valueindex_t index, bool value) {
    if (__coreIfc->stdb != 0) {
        tMsgDBValue *msg = new tMsgDBValue;

        msg->id=eMsgDBValueU64;
        msg->objid=objid;
        msg->valueid=valueid;
        msg->index=index;
        msg->action=eValueUpdate;
        msg->value.u64=value;
        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_createdata(objectid_t objid, valueid_t valueid, valueindex_t index, int64_t value) {

    if (__coreIfc->stdb != 0) {
        tMsgDBValue *msg = new tMsgDBValue;

        msg->id=eMsgDBValueI64;
        msg->objid=objid;
        msg->valueid=valueid;
        msg->index=index;
        msg->action=eValueCreate;
        msg->value.i64=value;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_updatedata(objectid_t objid, valueid_t valueid, valueindex_t index, int64_t value) {
    if (__coreIfc->stdb != 0) {
        tMsgDBValue *msg = new tMsgDBValue;

        msg->id=eMsgDBValueI64;
        msg->objid=objid;
        msg->valueid=valueid;
        msg->index=index;
        msg->action=eValueUpdate;
        msg->value.i64=value;

        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_deleteintdata(objectid_t objid, valueid_t valueid, valueindex_t index) {

    if (__coreIfc->stdb != 0) {
        tMsgDBValue *msg = new tMsgDBValue;

        msg->id=eMsgDBValueI64;
        msg->objid=objid;
        msg->valueid=valueid;
        msg->index=index;
        msg->action=eValueDelete;
        msg->value.i64 = 0;
        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_createdata(objectid_t objid, valueid_t valueid, valueindex_t index, const char*value) {
    if (__coreIfc->stdb != 0) {
        tMsgDBValue *msg = new tMsgDBValue;

        msg->id=eMsgDBValueString;
        msg->objid=objid;
        msg->valueid=valueid;
        msg->index=index;
        msg->action=eValueCreate;
        if (value != 0) {
            msg->value.str=strdup(value);
        } else {
            msg->value.str=strdup("<null>");
        }

        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_updatedata(objectid_t objid, valueid_t valueid, valueindex_t index, const char*value) {

    if (__coreIfc->stdb != 0) {
        tMsgDBValue *msg = new tMsgDBValue;

        msg->id=eMsgDBValueString;
        msg->objid=objid;
        msg->valueid=valueid;
        msg->index=index;
        msg->action=eValueUpdate;
        if (value != 0) {
            msg->value.str=strdup(value);
        } else {
            msg->value.str=strdup("<null>");
        }
        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_deletetextdata(objectid_t objid, valueid_t valueid, valueindex_t index) {

    if (__coreIfc->stdb != 0) {
        tMsgDBValue *msg = new tMsgDBValue;

        msg->id=eMsgDBValueString;
        msg->objid=objid;
        msg->valueid=valueid;
        msg->index=index;
        msg->action=eValueDelete;
        msg->value.str=strdup("<null>");

        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_createreferencedata(objectid_t objid, valueid_t valueid, valueindex_t index, objectid_t reference) {

    if (__coreIfc->stdb != 0) {
        tMsgDBValue *msg = new tMsgDBValue;

        msg->id=eMsgDBValueReference;
        msg->objid=objid;
        msg->valueid=valueid;
        msg->index=index;
        msg->action=eValueCreate;
        msg->value.u64=reference;
        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_updatereferencedata(objectid_t objid, valueid_t valueid, valueindex_t index, objectid_t reference) {

    if (__coreIfc->stdb != 0) {
        tMsgDBValue *msg = new tMsgDBValue;

        msg->id=eMsgDBValueReference;
        msg->objid=objid;
        msg->valueid=valueid;
        msg->index=index;
        msg->action=eValueUpdate;
        msg->value.u64=reference;
        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_deletereferencedata(objectid_t objid, valueid_t valueid, valueindex_t index) {

    if (__coreIfc->stdb != 0) {
        tMsgDBValue *msg = new tMsgDBValue;

        msg->id=eMsgDBValueReference;
        msg->objid=objid;
        msg->valueid=valueid;
        msg->index=index;
        msg->action=eValueDelete;
        msg->value.u64=0;
        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}


void stdb_set(uint8_t attrtype, objectid_t objid, valueid_t valueid, valueindex_t index, const tVariant& aValue) {
    if (__coreIfc->stdb != 0) {
        tMsgDBSet* msg = new tMsgDBSet(attrtype, objid, valueid, index, aValue);
        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_del(uint8_t attrtype, objectid_t objid, valueid_t valueid, valueindex_t index) {

    if (__coreIfc->stdb != 0) {
        tMsgDBValue *msg = new tMsgDBValue;

        switch(attrtype) {
        case 0x01:
            msg->id=eMsgDBValueDouble;
            break;
        case 0x02:
            msg->id=eMsgDBValueI64;
            break;
        case 0x04:
            msg->id=eMsgDBValueString;
            break;
        case 0x08:
            msg->id=eMsgDBValueReference;
            break;
        default:
            break;
        }

        msg->objid=objid;
        msg->valueid=valueid;
        msg->index=index;
        msg->action=eValueDelete;
        msg->handle = __coreIfc->stdbhandle;
        __coreIfc->stdb->Put(msg);
    }
}

void stdb_sqlexecstring(tCommTarget sender, uint64_t cmdtype, const char *cmd, uint64_t limit) {
    tSigSQLExecStringReq* msg= new tSigSQLExecStringReq;\
\
    msg->src     = sender;
    msg->handle  = __coreIfc->stdbhandle;
    msg->src     = sender;
    msg->CmdType = cmdtype;
    msg->Limit   = limit;
    msg->SQL     = cmd;

    __coreIfc->stdb->Put(msg);
}

void stdb_fetch(tCommTarget sender, uint64_t cmdType, uint64_t limit) {
    tSigSQLFetchReq* msg = new tSigSQLFetchReq;

    msg->src     = sender;
    msg->cmdType = cmdType;
    msg->handle  = __coreIfc->stdbhandle;
    msg->Limit   = limit;

    __coreIfc->stdb->Put(msg);
}


#define DB_OPEN(db) \
void open(tCommTarget sender, std::string name, std::string host, std::string port, std::string user, std::string passwd) {\
    tSigSQLConnectReq* msg = new tSigSQLConnectReq;\
\
    msg->src   = sender;\
    msg->name  = name;\
    msg->host  = host;\
    msg->port  = port;\
    msg->user  = user;\
    msg->passwd = passwd;\
\
    db->Put(msg);\
}

#define DB_EXECSTRING(db)\
void sqlexecstring(tCommTarget sender, int handle, uint64_t cmdtype, const char* cmd, uint32_t limit) {\
    tSigSQLExecStringReq* msg= new tSigSQLExecStringReq;\
\
    msg->src     = sender;\
    msg->handle  = handle;\
    msg->src     = sender;\
    msg->CmdType = cmdtype;\
    msg->Limit   = limit;\
    msg->SQL     = cmd;\
\
    db->Put(msg);\
}

#define DB_FETCH(db)\
void sqlfetch(tCommTarget sender, int handle, uint32_t limit) {\
    tSigSQLFetchReq* msg = new tSigSQLFetchReq;\
\
    msg->src    = sender;\
    msg->handle = handle;\
    msg->Limit  = limit;\
\
    db->Put(msg);\
}

#define DB_CLOSE(db)\
void close(tCommTarget sender, int handle) {\
    tSigSQLDisconnectReq* msg = new tSigSQLDisconnectReq;\
\
    msg->src    = sender;\
    msg->handle = handle;\
\
    db->Put(msg);\
}

namespace stdb {
    DB_OPEN(__coreIfc->stdb)
    DB_EXECSTRING(__coreIfc->stdb)
    DB_FETCH(__coreIfc->stdb)
    DB_CLOSE(__coreIfc->stdb)
}

namespace pgdb {
    DB_OPEN(__coreIfc->pgdb)
    DB_EXECSTRING(__coreIfc->pgdb)
    DB_FETCH(__coreIfc->pgdb)
    DB_CLOSE(__coreIfc->pgdb)
}

namespace mariadb {
    DB_OPEN(__coreIfc->mariadb)
    DB_EXECSTRING(__coreIfc->mariadb)
    DB_FETCH(__coreIfc->mariadb)
    DB_CLOSE(__coreIfc->mariadb)
}

objectid_t to_objectid_t(tJSON *j) {
    objectid_t retval = 0ul;

    if (j != nullptr) {
        retval = static_cast<objectid_t>(to_uint64_t(j));
    }
    return retval;
}

