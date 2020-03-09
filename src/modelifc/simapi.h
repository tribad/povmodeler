#ifndef SIMAPI_H
#define SIMAPI_H

#include <simobj.h>
#include <simattrarray.h>

#define STDB_SQL_EXECLIMIT 10000
//
// CoreIfc access functions.
void ScheduleSignal(tSig *sig);
void ScheduleMsg(tMsg* msg);
void StartObject(tSimObj* obj);
void FreeObject(tSimObj* obj);
//
//  This function removes an object from the simulation.
//  Any processing needed for clean up is done here.
//  Final removal is done in the simulation thread.
void     DeleteObject(tSimObj* obj);
//
//  Setting the absolut cycle of the simulation.
//  Only the absolut-cycle can be set to a specific value.
void SetCycle(uint64_t aCycle);
uint64_t GetCycle(void);

tMsg* SendMsg(const tSimAttrArrayIter& iter, tMsg* msg);
tMsg* SendMsg(const tSimObjRef& aRef, tMsg* aMsg);
tMsg* SendMsg(const tSimObjRefIter& aRef, tMsg* aMsg);
tMsg* SendMsg(tSimObj* aRef, tMsg* aMsg);
tMsg* SendMsg(tMsg* aMsg);
void SendSig(const tSimAttrArrayIter& iter, tSig* sig);
void SendSig(const tSimObjRef& aRef, tSig* aSig);
void SendSig(const tSimObjRefIter& aRef, tSig* aSig);
void SendSig(tSimObj* aRef, tSig* aSig);
void SendSig(tSig* aSig);

tMsg* SendMsgToParent(const tSimAttrArrayIter& iter, tMsg* msg);
tMsg* SendMsgToParent(const tSimObjRef& aRef, tMsg* aMsg);
tMsg* SendMsgToParent(const tSimObjRefIter& aRef, tMsg* aMsg);
void SendSigToParent(const tSimAttrArrayIter& iter, tSig* sig);
void SendSigToParent(const tSimObjRef& aRef, tSig* aSig);
void SendSigToParent(const tSimObjRefIter& aRef, tSig* aSig);

tSimObj* GetParent(const tSimAttrArrayIter& iter);
tSimObj* GetParent(const tSimObjRef& aRef);
tSimObj* GetParent(const tSimObjRefIter& aRef);

tVariant GetValue(const tSimAttrArrayIter& iter, uint64_t vid, uint64_t vidx);
tVariant GetValue(const tSimAttrArrayIter& iter, uint64_t vid);
void SetValue(const tSimAttrArrayIter& iter, uint64_t vid, uint64_t vidx, const tVariant& value);
void SetValue(const tSimAttrArrayIter& iter, uint64_t vid, const tVariant& value);

tVariant GetValue(const tSimObjRefIter& iter, uint64_t vid, uint64_t vidx);
tVariant GetValue(const tSimObjRefIter& iter, uint64_t vid);
void SetValue(const tSimObjRefIter& iter, uint64_t vid, uint64_t vidx, const tVariant& value);
void SetValue(const tSimObjRefIter& iter, uint64_t vid, const tVariant& value);

tVariant GetValue(const tSimObjRef& ref, uint64_t vid, uint64_t vidx);
tVariant GetValue(const tSimObjRef& ref, uint64_t vid);
void SetValue(const tSimObjRef& ref, uint64_t vid, uint64_t vidx, const tVariant& value);
void SetValue(const tSimObjRef& ref, uint64_t vid, const tVariant& value);

tVariant GetValue(tSimObj* obj, uint64_t vid, uint64_t vidx);
tVariant GetValue(tSimObj* obj, uint64_t vid);
void SetValue(tSimObj* obj, uint64_t vid, uint64_t vidx, const tVariant& value);
void SetValue(tSimObj* obj, uint64_t vid, const tVariant& value);

//
//  Wrappers for direct access to the db.
//  All these functions work asynchronous.
//  We use different Namespaces to destinguish between the different DB-Types. Its up to the application to make the decission.
namespace mariadb {
    extern void open(tCommTarget sender, std::string name, std::string host="", std::string port="", std::string user="", std::string passwd="");
    extern void sqlexecstring(tCommTarget sender, int handle, uint64_t cmdtype, const char* cmd, uint32_t limit = (uint32_t)-1 );
    extern void sqlfetch(tCommTarget sender, int handle, uint32_t limit = (uint32_t)-1);
    extern void close(tCommTarget sender, int handle);
}

namespace pgdb {
    extern void open(tCommTarget sender, std::string name, std::string host="", std::string port="", std::string user="", std::string passwd="");
    extern void sqlexecstring(tCommTarget sender, int handle, uint64_t cmdtype, const char* cmd, uint32_t limit = (uint32_t)-1 );
    extern void sqlfetch(tCommTarget sender, int handle, uint32_t limit = (uint32_t)-1);
    extern void close(tCommTarget sender, int handle);
}

namespace stdb {
    extern void open(tCommTarget sender, std::string name, std::string host="", std::string port="", std::string user="", std::string passwd="");
    extern void sqlexecstring(tCommTarget sender, int handle, uint64_t cmdtype, const char* cmd, uint32_t limit = (uint32_t)-1 );
    extern void sqlfetch(tCommTarget sender, int handle, uint32_t limit = (uint32_t)-1);
    extern void close(tCommTarget sender, int handle);
}
/*
 * These are more sophisticated wrappers to the CoreIfc Structure
 */
extern void stdb_createobj(objectid_t objid, uint64_t type) ;
extern void stdb_createfromtemplate(uint32_t templateid, uint32_t objid, uint64_t type) ;
extern void stdb_deleteobj(objectid_t objid) ;

extern void stdb_createdata(objectid_t objid, valueid_t valueid, valueindex_t index, double value) ;
extern void stdb_updatedata(objectid_t objid, valueid_t valueid, valueindex_t index, double value) ;
extern void stdb_deletefloatdata(objectid_t objid, valueid_t valueid, valueindex_t index) ;
extern void stdb_set(objectid_t objid, valueid_t valueid, valueindex_t index, double value);
extern void stdb_createdata(objectid_t objid, valueid_t valueid, valueindex_t index, uint64_t value) ;
extern void stdb_updatedata(objectid_t objid, valueid_t valueid, valueindex_t index, uint64_t value) ;
extern void stdb_set(objectid_t objid, valueid_t valueid, valueindex_t index, uint64_t value);
extern void stdb_createdata(objectid_t objid, valueid_t valueid, valueindex_t index, bool value) ;
extern void stdb_updatedata(objectid_t objid, valueid_t valueid, valueindex_t index, bool value) ;
extern void stdb_set(objectid_t objid, valueid_t valueid, valueindex_t index, bool value);
extern void stdb_createdata(objectid_t objid, valueid_t valueid, valueindex_t index, int64_t value) ;
extern void stdb_updatedata(objectid_t objid, valueid_t valueid, valueindex_t index, int64_t value) ;
extern void stdb_deleteintdata(objectid_t objid, valueid_t valueid, valueindex_t index) ;
extern void stdb_set(objectid_t objid, valueid_t valueid, valueindex_t index, int64_t value);
extern void stdb_createdata(objectid_t objid, valueid_t valueid, valueindex_t index, const char*value) ;
extern void stdb_updatedata(objectid_t objid, valueid_t valueid, valueindex_t index, const char*value) ;
extern void stdb_deletetextdata(objectid_t objid, valueid_t valueid, valueindex_t index) ;
extern void stdb_set(objectid_t objid, valueid_t valueid, valueindex_t index, const char* value);
extern void stdb_createreferencedata(objectid_t objid, valueid_t valueid, valueindex_t index, objectid_t reference) ;
extern void stdb_updatereferencedata(objectid_t objid, valueid_t valueid, valueindex_t index, objectid_t reference) ;
extern void stdb_deletereferencedata(objectid_t objid, valueid_t valueid, valueindex_t index) ;
extern void stdb_sqlexecstring(tCommTarget sender, uint64_t cmdtype, const char* cmd, uint64_t limit = STDB_SQL_EXECLIMIT);
extern void stdb_fetch(tCommTarget sender, uint64_t cmdtype, uint64_t limit = STDB_SQL_EXECLIMIT);
/*
 * JSON helper.
 * As the JSON parser works on standard data types and is used by different applications the
 * extensions needed for the simulation are defined here.
 */
objectid_t to_objectid_t(tJSON* j);


#endif // SIMAPI_H
