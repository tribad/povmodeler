// *************************************************************************************************************
//
//  Modul-Name     : CMainViewport.cpp
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
#include "CMainViewport.h"
// Optional
#include <string>
#include "../messages/tMsgStartImportReq.h"
#include "../messages/tMsgStartImportReply.h"
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
static std::map<objectid_t, CMainViewport*> t_store;
/*
 *
 *       !!!!    Here is a collection of functions that are editable.   !!!!
 */
/* **************************************************************************
 *
 *  Method-Name   : startimportreq()
 *
 *  Partial generated source code.
 *
 * *************************************************************************/
tMsg* CMainViewport::process(tMsgStartImportReq* msg) {
    tMsg* retval=0;
// User-Defined-Code:startimportreq
    tMsgStartImportReply* reply = new tMsgStartImportReply;
    //
    // Create and init a new project
    tSimObj* newproj = NewObject(IDO_PROJECT, this);

    if (newproj != nullptr) {
        //
        //  Setting up the reference to the project into the projects array
        //  and send the project the start import request.
        //  So the project can init itself as needed.
        tVariant objref = tObjectRef { newproj->objid, newproj};

        contained[0] = objref;
        //
        //  The project shall not delete the message.
        SendMsg(newproj, msg);
    }
    //
    //  Make the reply ready.
    reply->dst.type        = eCommTarget::Node;
    reply->dst.node.nodeid = 0;
    //
    //  We return the filename back to the modeller so it can do the loading
    //  Within its own statemachine.
    reply->FileName = msg->FileName;
    //
    //  Exit sequence
    retval = reply;

    delete msg;
// End-Of-UDC:startimportreq
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
// User-Defined-Code: save-mainviewport
// End-Of-UDC: save-mainviewport
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
    CMainViewport* mainviewport_var = (CMainViewport*)obj;

    switch (valueid) {
    case IDA_CONTAINED:
        *((tVariant*)(&mainviewport_var->contained[valueindex])) = tSimObjRef(value, simidx.Find(value));
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
    CMainViewport* mainviewport_var = (CMainViewport*)obj;

    switch (valueid) {
    case IDA_CONTAINED:
        retval = mainviewport_var->contained[valueindex];
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
    CMainViewport* mainviewport_var = (CMainViewport*)obj;

    switch (valueid) {
    case IDA_CONTAINED:
        mainviewport_var->contained[valueindex] = value;
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
    CMainViewport* thisobj = (CMainViewport*)obj;
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
bool CMainViewport::DefaultSigHandler(tSig *sig) {
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
tMsg* CMainViewport::DefaultMsgHandler(tMsg *msg) {
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
    CMainViewport* thisobj = (CMainViewport*)obj;

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
    CMainViewport*thisobj=(CMainViewport*)obj;
    tMsg *retmsg=0;

    switch (msg->id) {
    case IDM_STARTIMPORTREQ:
        retmsg = thisobj->process((tMsgStartImportReq*)(msg));
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
//  Method-Name   : create_mainviewport_obj()
//
//  Generated source code.
//
// **************************************************************************
static tSimObj* create_mainviewport_obj(objectid_t  oid) {
    CMainViewport* newmainviewport = new CMainViewport;

    if (newmainviewport != 0) {
        tSimObj* newobj = newmainviewport;

        newobj->type        = IDO_MAINVIEWPORT;
        newobj->objid       = oid;
        newobj->parent      = 0;
        newobj->setvalue    = setvalue;
        newobj->getvalue    = getvalue;
        newobj->save        = save;
        newobj->update      = init_object;
        newobj->process     = process_sig;
        newobj->syncprocess = process_msg;
        if (0xc0000000 & oid) {
            t_store.insert(std::pair<templateid_t, CMainViewport*>(oid, newmainviewport));
        }
        newmainviewport->contained = CSimAttrArray(oid, IDA_CONTAINED, eSimAttrType::Reference);
    } else {
    }
    return ((tSimObj*)newmainviewport);
}
// **************************************************************************
//
//  Method-Name   : create_new_mainviewport_obj()
//
//  Generated source code.
//
// **************************************************************************
static tSimObj* create_new_mainviewport_obj(objectid_t  oid) {
    CMainViewport* newmainviewport = new CMainViewport;

    if (newmainviewport != 0) {
        tSimObj* newobj = newmainviewport;

        newobj->type        = IDO_MAINVIEWPORT;
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
        stdb_createobj(oid, IDO_MAINVIEWPORT);
        //
        //  Now fill the attributes with values.
        newmainviewport->contained = CSimAttrArray(oid, IDA_CONTAINED, eSimAttrType::Reference);
        //
        //  create the attribute data in the DB.
    } else {
    }
    return ((tSimObj*)newmainviewport);
}
// **************************************************************************
//
//  Method-Name   : create_new_mainviewport_obj_from_template()
//
//  Generated source code.
//
// **************************************************************************
static tSimObj* create_new_mainviewport_obj_from_template(templateid_t  tid, objectid_t  oid) {
    CMainViewport* newmainviewport = 0;
    std::map<objectid_t, CMainViewport*>::iterator found;

    found = t_store.find(tid);
    if (found != t_store.end()) {
        newmainviewport = new CMainViewport;
        if (newmainviewport != 0) {
            tSimObj* newobj = newmainviewport;

            newobj->type        = IDO_MAINVIEWPORT;
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
            stdb_createobj(oid, IDO_MAINVIEWPORT);
            //
            newmainviewport->contained = CSimAttrArray(oid, IDA_CONTAINED, eSimAttrType::Reference);
            //
            //  Copy data from template.
            //
        } else {
        }
    } else {
    }
    return ((tSimObj*)newmainviewport);
}

tObjLib mainviewport_factory= {0, 0, 0, IDO_MAINVIEWPORT, create_mainviewport_obj, create_new_mainviewport_obj, create_new_mainviewport_obj_from_template};
