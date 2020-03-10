// *************************************************************************************************************
//
//  Modul-Name     : CObjectBase.cpp
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
//
//                      S y s t e m   i n c l u d e s
#include <stdint.h>
#include <stdlib.h>
#include <simifc.h>
#include <simattribute.h>
#include <simobjfactory.h>
#include <simapi.h>
#include <pointerindex.h>
#include <vector>
#include <map>
#include "generated.h"
#include "ids.h"
//
//                       M o d e l   i n c l u d e s
#include "CObjectBase.h"
// Optional
/*
 *  private macros
 */
/*
 * These are function prototypes for local object functions defined within 
 * the simulation object.
 */
static int setvaluedb(tSimObj * obj, valueid_t  valueid, valueindex_t  valueindex, const tVariant& value);
static int setvalue(tSimObj * obj, valueid_t  valueid, valueindex_t  valueindex, const tVariant&  value);
/*
 *  The template storage map
 */
static std::map<objectid_t, CObjectBase*> t_store;
/*
 *
 *       !!!!    Here is a collection of functions that are editable.   !!!!
 */
// **************************************************************************
//
//  Method-Name   : save()
//
//  Generated source code.
//
// **************************************************************************
static int save(tSimObj* obj, uint64_t aCycle, ... ) {
    int result = 0;
// User-Defined-Code: save-cobjectbase
// End-Of-UDC: save-cobjectbase
    return (result);
}

//
//
//       !!!!          End of editable section of functions.             !!!!
//
// FH ************************************************************************
//
//  Method-Name   : setvalue()
//
// **************************************************************************
static int setvalue(tSimObj * obj, valueid_t  valueid, valueindex_t  valueindex, const tVariant& value) {
    int err = 0;
    CObjectBase* cobjectbase_var = (CObjectBase*)obj;

    switch (valueid) {
    case IDA_NAME:
        *((tVariant*)(&cobjectbase_var->Name)) = value;
        break;
    case IDA_OBJECTSBEFORE:
        cobjectbase_var->ObjectsBefore[valueindex] = value;
        break;
    case IDA_OBJECTSAFTER:
        cobjectbase_var->ObjectsAfter[valueindex] = value;
        break;
    default:
        err = -1;
        break;
    }
    return (err);
}
// FH ************************************************************************
//
//  Method-Name   : getvalue()
//
// **************************************************************************
static tVariant getvalue(tSimObj * obj, valueid_t  valueid, valueindex_t  valueindex) {
    tVariant retval;
    CObjectBase* cobjectbase_var = (CObjectBase*)obj;

    switch (valueid) {
    case IDA_NAME:
        retval = cobjectbase_var->Name;
        break;
    default:
        break;
    }
    return (retval);
}
// FH ************************************************************************
//
//  Method-Name   : setvaluedb()
//
// **************************************************************************
static int setvaluedb(tSimObj * obj, valueid_t  valueid, valueindex_t  valueindex, const tVariant& value) {
    int err=0;
    CObjectBase* cobjectbase_var = (CObjectBase*)obj;

    switch (valueid) {
    case IDA_NAME:
        cobjectbase_var->Name = value;
        break;
    case IDA_OBJECTSBEFORE:
        cobjectbase_var->ObjectsBefore[valueindex] = value;
        break;
    case IDA_OBJECTSAFTER:
        cobjectbase_var->ObjectsAfter[valueindex] = value;
        break;
    default:
        err=-1;
        break;
    }
    return (err);
}
// **************************************************************************
//
//  Method-Name   : init_object()
//
//  Generated source code.
//
// **************************************************************************
static void init_object(tSimObj * obj, uint64_t  aCycle) {
    CObjectBase* thisobj = (CObjectBase*)obj;
    /*
     * Fill all references with the pointers.
     */
    /*
     *  This object has no statemachine.
     */
    obj->update   = 0;
    /*
     *  Switch over to update the DB as well if object attributes change.
     */
    obj->setvalue = setvaluedb;
}
// **************************************************************************
//
//  Method-Name   : DefaultSigHandler()
//
//  Generated source code.
//
// **************************************************************************
bool CObjectBase::DefaultSigHandler(tSig *sig) {
    bool retval = false;
// User-Defined-Code: default-sig-handler
// End-Of-UDC: default-sig-handler
    return (retval);
}

// **************************************************************************
//
//  Method-Name   : DefaultMsgHandler()
//
//  Generated source code.
//
// **************************************************************************
tMsg* CObjectBase::DefaultMsgHandler(tMsg *msg) {
    tMsg* retval = 0;
// User-Defined-Code: default-msg-handler
// End-Of-UDC: default-msg-handler
    return retval;
}

// **************************************************************************
//
//  Method-Name   : process_sig()
//
//  Generated source code.
//
// **************************************************************************
static void process_sig(tSimObj * obj, tSig *sig) {
    CObjectBase* thisobj = (CObjectBase*)obj;

    switch (sig->id) {
    default:
        if ((sig->type == MSG_TYPE_INDICATION) && (obj->parent != 0) && (obj!=obj->parent)) {
            sig->dst.obj.id  = obj->parent->objid;
            sig->dst.obj.ptr = obj->parent;
            sig->dst.type    = eCommTarget::Object;
            ScheduleSignal(sig);
        } else {
            bool processed = thisobj->DefaultSigHandler(sig);
            if (!processed) {
                delete sig;
            }
        }
        break;
    }
}
// **************************************************************************
//
//  Method-Name   : process_msg()
//
//  Generated source code.
//
// **************************************************************************
static tMsg* process_msg(tSimObj * obj, tMsg * msg) {
    CObjectBase*thisobj=(CObjectBase*)obj;
    tMsg *retmsg=0;

    switch (msg->id) {
    default:
        if (((msg->type == MSG_TYPE_REPLY) || (msg->type == MSG_TYPE_INDICATION)) && (obj->parent != 0) && (obj != obj->parent)) {
            retmsg = obj->parent->syncprocess(obj->parent, msg);
        } else {
            retmsg = thisobj->DefaultMsgHandler(msg);
        }
        break;
    }
    return (retmsg);
}
// **************************************************************************
//
//  Method-Name   : create_cobjectbase_obj()
//
//  Generated source code.
//
// **************************************************************************
static tSimObj* create_cobjectbase_obj(objectid_t  oid) {
    CObjectBase* newcobjectbase = new CObjectBase;

    if (newcobjectbase != 0) {
        tSimObj* newobj = newcobjectbase;

        newobj->type        = IDO_COBJECTBASE;
        newobj->objid       = oid;
        newobj->parent      = 0;
        newobj->setvalue    = setvalue;
        newobj->getvalue    = getvalue;
        newobj->save        = save;
        newobj->update      = init_object;
        newobj->process     = process_sig;
        newobj->syncprocess = process_msg;
        if (0xc0000000 & oid) {
            t_store.insert(std::pair<templateid_t, CObjectBase*>(oid, newcobjectbase));
        }
    } else {
    }
    return ((tSimObj*)newcobjectbase);
}
// **************************************************************************
//
//  Method-Name   : create_new_cobjectbase_obj()
//
//  Generated source code.
//
// **************************************************************************
static tSimObj* create_new_cobjectbase_obj(objectid_t  oid) {
    CObjectBase* newcobjectbase = new CObjectBase;

    if (newcobjectbase != 0) {
        tSimObj* newobj = newcobjectbase;

        newobj->type        = IDO_COBJECTBASE;
        newobj->objid       = oid;
        newobj->parent      = 0;
        newobj->setvalue    = setvalue;
        newobj->getvalue    = getvalue;
        newobj->save        = save;
        newobj->update      = init_object;
        newobj->process     = process_sig;
        newobj->syncprocess = process_msg;
        //
        //  Create the object in the db.
        stdb_createobj(oid, IDO_COBJECTBASE);
        //
        //  Now fill the attributes with values.
        //
        //  create the attribute data in the DB.
    } else {
    }
    return ((tSimObj*)newcobjectbase);
}
// **************************************************************************
//
//  Method-Name   : create_new_cobjectbase_obj_from_template()
//
//  Generated source code.
//
// **************************************************************************
static tSimObj* create_new_cobjectbase_obj_from_template(templateid_t  tid, objectid_t  oid) {
    CObjectBase* newcobjectbase = 0;
    std::map<objectid_t, CObjectBase*>::iterator found;

    found = t_store.find(tid);
    if (found != t_store.end()) {
        newcobjectbase = new CObjectBase;
        if (newcobjectbase != 0) {
            tSimObj* newobj = newcobjectbase;

            newobj->type        = IDO_COBJECTBASE;
            newobj->objid       = oid;
            newobj->parent      = 0;
            newobj->setvalue    = setvalue;
            newobj->getvalue    = getvalue;
            newobj->save        = save;
            newobj->update      = init_object;
            newobj->process     = process_sig;
            newobj->syncprocess = process_msg;
            //
            //  Create the object in the db.
            stdb_createobj(oid, IDO_COBJECTBASE);
            //
            //
            //  Copy data from template.
            newcobjectbase->ObjectsBefore = found->second->ObjectsBefore;
            newcobjectbase->ObjectsAfter = found->second->ObjectsAfter;
            //
        } else {
        }
    } else {
    }
    return ((tSimObj*)newcobjectbase);
}

tObjLib cobjectbase_factory= {0, 0, 0, IDO_COBJECTBASE, create_cobjectbase_obj, create_new_cobjectbase_obj, create_new_cobjectbase_obj_from_template};
