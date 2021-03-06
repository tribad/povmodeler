// *************************************************************************************************************
//
//  Modul-Name     : CProject.cpp
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
#include "CProject.h"
// Optional
#include <string>
#include "../messages/tMsgStartImportReq.h"
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
static std::map<objectid_t, CProject*> t_store;
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
tMsg* CProject::process(tMsgStartImportReq* msg) {
    tMsg* retval=0;
// User-Defined-Code:startimportreq
    //
    //  First setup the values from the message as needed.
    FileName = msg->FileName;
    //
    // Create and init a new project
    tSimObj* newscene = NewObject(IDO_SCENE, this);

    if (newscene != nullptr) {
        //
        //  Setting up the reference to the project into the projects array
        //  and send the project the start import request.
        //  So the project can init itself as needed.
        tVariant objref = tObjectRef { newscene->objid, newscene};

        SetValue(this, IDA_SCENES, objref);
        //
        //  The project shall not delete the message.
        SendMsg(newscene, msg);
    }
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
// User-Defined-Code: save-project
// End-Of-UDC: save-project
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
    CProject* project_var = (CProject*)obj;

    switch (valueid) {
    case IDA_FILENAME:
        *((tVariant*)(&project_var->FileName)) = value;
        break;
    case IDA_NAME:
        *((tVariant*)(&project_var->Name)) = value;
        break;
    case IDA_OBJECTSBEFORE:
        project_var->ObjectsBefore[valueindex] = value;
        break;
    case IDA_OBJECTSAFTER:
        project_var->ObjectsAfter[valueindex] = value;
        break;
    case IDA_SCENES:
        *((tVariant*)(&project_var->Scenes[valueindex])) = tSimObjRef(value, simidx.Find(value));
        break;
    case IDA_CONTAINED:
        *((tVariant*)(&project_var->contained[valueindex])) = tSimObjRef(value, simidx.Find(value));
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
    CProject* project_var = (CProject*)obj;

    switch (valueid) {
    case IDA_FILENAME:
        retval = project_var->FileName;
        break;
    case IDA_SCENES:
        retval = project_var->Scenes[valueindex];
        break;
    case IDA_NAME:
        retval = project_var->Name;
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
    CProject* project_var = (CProject*)obj;

    switch (valueid) {
    case IDA_FILENAME:
        project_var->FileName = value;
        break;
    case IDA_SCENES:
        project_var->Scenes[valueindex] = value;
        break;
    case IDA_NAME:
        project_var->Name = value;
        break;
    case IDA_OBJECTSBEFORE:
        project_var->ObjectsBefore[valueindex] = value;
        break;
    case IDA_OBJECTSAFTER:
        project_var->ObjectsAfter[valueindex] = value;
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
    CProject* thisobj = (CProject*)obj;
    /*
     * Fill all references with the pointers.
     */
    for (tSimAttrArrayIter i = thisobj->Scenes.begin(); i != thisobj->Scenes.end(); ++i) {
        i->second.ptr = simidx.Find(i->second.ul);
        if (i->second.ptr != 0) {
            ((tSimObj*)(i->second.ptr))->parent = obj;
        }
    }
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
bool CProject::DefaultSigHandler(tSig *sig) {
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
tMsg* CProject::DefaultMsgHandler(tMsg *msg) {
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
    CProject* thisobj = (CProject*)obj;

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
    CProject*thisobj=(CProject*)obj;
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
//  Method-Name   : create_project_obj()
//
//  Generated source code.
//
// **************************************************************************
static tSimObj* create_project_obj(objectid_t  oid) {
    CProject* newproject = new CProject;

    if (newproject != 0) {
        tSimObj* newobj = newproject;

        newobj->type        = IDO_PROJECT;
        newobj->objid       = oid;
        newobj->parent      = 0;
        newobj->setvalue    = setvalue;
        newobj->getvalue    = getvalue;
        newobj->save        = save;
        newobj->update      = init_object;
        newobj->process     = process_sig;
        newobj->syncprocess = process_msg;
        if (0xc0000000 & oid) {
            t_store.insert(std::pair<templateid_t, CProject*>(oid, newproject));
        }
        newproject->Scenes = CSimAttrArray(oid, IDA_SCENES, eSimAttrType::Reference);
    } else {
    }
    return ((tSimObj*)newproject);
}
// **************************************************************************
//
//  Method-Name   : create_new_project_obj()
//
//  Generated source code.
//
// **************************************************************************
static tSimObj* create_new_project_obj(objectid_t  oid) {
    CProject* newproject = new CProject;

    if (newproject != 0) {
        tSimObj* newobj = newproject;

        newobj->type        = IDO_PROJECT;
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
        stdb_createobj(oid, IDO_PROJECT);
        //
        //  Now fill the attributes with values.
        newproject->Scenes = CSimAttrArray(oid, IDA_SCENES, eSimAttrType::Reference);
        //
        //  create the attribute data in the DB.
    } else {
    }
    return ((tSimObj*)newproject);
}
// **************************************************************************
//
//  Method-Name   : create_new_project_obj_from_template()
//
//  Generated source code.
//
// **************************************************************************
static tSimObj* create_new_project_obj_from_template(templateid_t  tid, objectid_t  oid) {
    CProject* newproject = 0;
    std::map<objectid_t, CProject*>::iterator found;

    found = t_store.find(tid);
    if (found != t_store.end()) {
        newproject = new CProject;
        if (newproject != 0) {
            tSimObj* newobj = newproject;

            newobj->type        = IDO_PROJECT;
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
            stdb_createobj(oid, IDO_PROJECT);
            //
            newproject->Scenes = CSimAttrArray(oid, IDA_SCENES, eSimAttrType::Reference);
            //
            //  Copy data from template.
            newproject->ObjectsBefore = found->second->ObjectsBefore;
            newproject->ObjectsAfter = found->second->ObjectsAfter;
            //
        } else {
        }
    } else {
    }
    return ((tSimObj*)newproject);
}

tObjLib project_factory= {0, 0, 0, IDO_PROJECT, create_project_obj, create_new_project_obj, create_new_project_obj_from_template};
