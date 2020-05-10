// *************************************************************************************************************
//
//  Modul-Name     : CLightSource.cpp
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
#include "CLightSource.h"
// Optional
#include <string>
#include "../messages/eModelElementFormat.h"
#include "../messages/tElementProperty.h"
#include "../messages/tMsgAddElementReq.h"
#include "../messages/tMsgAddElementReply.h"
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
static std::map<objectid_t, CLightSource*> t_store;
/*
 *
 *       !!!!    Here is a collection of functions that are editable.   !!!!
 */
/* **************************************************************************
 *
 *  Method-Name   : addelementreq()
 *
 *  Partial generated source code.
 *
 * *************************************************************************/
tMsg* CLightSource::process(tMsgAddElementReq* msg) {
    tMsg* retval=0;
// User-Defined-Code:addelementreq
// End-Of-UDC:addelementreq
    return (retval);
}
// **************************************************************************
//
//  Method-Name   : save()
//
//  Generated source code.
//
// **************************************************************************
static int save(tSimObj* obj, uint64_t aCycle, ... ) {
    int result = 0;
// User-Defined-Code: save-lightsource
// End-Of-UDC: save-lightsource
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
    CLightSource* lightsource_var = (CLightSource*)obj;

    switch (valueid) {
    case IDA_NAME:
        *((tVariant*)(&lightsource_var->Name)) = value;
        break;
    case IDA_OBJECTSBEFORE:
        lightsource_var->ObjectsBefore[valueindex] = value;
        break;
    case IDA_OBJECTSAFTER:
        lightsource_var->ObjectsAfter[valueindex] = value;
        break;
    case IDA_CONTAINED:
        *((tVariant*)(&lightsource_var->contained[valueindex])) = tSimObjRef(value, simidx.Find(value));
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
    CLightSource* lightsource_var = (CLightSource*)obj;

    switch (valueid) {
    case IDA_NAME:
        retval = lightsource_var->Name;
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
    CLightSource* lightsource_var = (CLightSource*)obj;

    switch (valueid) {
    case IDA_NAME:
        lightsource_var->Name = value;
        break;
    case IDA_OBJECTSBEFORE:
        lightsource_var->ObjectsBefore[valueindex] = value;
        break;
    case IDA_OBJECTSAFTER:
        lightsource_var->ObjectsAfter[valueindex] = value;
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
    CLightSource* thisobj = (CLightSource*)obj;
    /*
     * Fill all references with the pointers.
     */
    for (tSimAttrArrayIter i = thisobj->contained.begin(); i != thisobj->contained.end(); ++i) {
        i->second.ptr = simidx.Find(i->second.ul);
        if (i->second.ptr != 0) {
            ((tSimObj*)(i->second.ptr))->parent = obj;
        }
    }
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
bool CLightSource::DefaultSigHandler(tSig *sig) {
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
tMsg* CLightSource::DefaultMsgHandler(tMsg *msg) {
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
    CLightSource* thisobj = (CLightSource*)obj;

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
    CLightSource*thisobj=(CLightSource*)obj;
    tMsg *retmsg=0;

    switch (msg->id) {
    case IDM_ADDELEMENTREQ:
        retmsg = thisobj->process((tMsgAddElementReq*)(msg));
        break;
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
//  Method-Name   : create_lightsource_obj()
//
//  Generated source code.
//
// **************************************************************************
static tSimObj* create_lightsource_obj(objectid_t  oid) {
    CLightSource* newlightsource = new CLightSource;

    if (newlightsource != 0) {
        tSimObj* newobj = newlightsource;

        newobj->type        = IDO_LIGHTSOURCE;
        newobj->objid       = oid;
        newobj->parent      = 0;
        newobj->setvalue    = setvalue;
        newobj->getvalue    = getvalue;
        newobj->save        = save;
        newobj->update      = init_object;
        newobj->process     = process_sig;
        newobj->syncprocess = process_msg;
        if (0xc0000000 & oid) {
            t_store.insert(std::pair<templateid_t, CLightSource*>(oid, newlightsource));
        }
    } else {
    }
    return ((tSimObj*)newlightsource);
}
// **************************************************************************
//
//  Method-Name   : create_new_lightsource_obj()
//
//  Generated source code.
//
// **************************************************************************
static tSimObj* create_new_lightsource_obj(objectid_t  oid) {
    CLightSource* newlightsource = new CLightSource;

    if (newlightsource != 0) {
        tSimObj* newobj = newlightsource;

        newobj->type        = IDO_LIGHTSOURCE;
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
        stdb_createobj(oid, IDO_LIGHTSOURCE);
        //
        //  Now fill the attributes with values.
        //
        //  create the attribute data in the DB.
    } else {
    }
    return ((tSimObj*)newlightsource);
}
// **************************************************************************
//
//  Method-Name   : create_new_lightsource_obj_from_template()
//
//  Generated source code.
//
// **************************************************************************
static tSimObj* create_new_lightsource_obj_from_template(templateid_t  tid, objectid_t  oid) {
    CLightSource* newlightsource = 0;
    std::map<objectid_t, CLightSource*>::iterator found;

    found = t_store.find(tid);
    if (found != t_store.end()) {
        newlightsource = new CLightSource;
        if (newlightsource != 0) {
            tSimObj* newobj = newlightsource;

            newobj->type        = IDO_LIGHTSOURCE;
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
            stdb_createobj(oid, IDO_LIGHTSOURCE);
            //
            //
            //  Copy data from template.
            newlightsource->ObjectsBefore = found->second->ObjectsBefore;
            newlightsource->ObjectsAfter = found->second->ObjectsAfter;
            //
        } else {
        }
    } else {
    }
    return ((tSimObj*)newlightsource);
}

tObjLib lightsource_factory= {0, 0, 0, IDO_LIGHTSOURCE, create_lightsource_obj, create_new_lightsource_obj, create_new_lightsource_obj_from_template};
