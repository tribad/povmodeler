// *************************************************************************************************************
//
//  Modul-Name     : CIsoSurface.cpp
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
#include "CIsoSurface.h"
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
static std::map<objectid_t, CIsoSurface*> t_store;
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
// User-Defined-Code: save-isosurface
// End-Of-UDC: save-isosurface
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
    CIsoSurface* isosurface_var = (CIsoSurface*)obj;

    switch (valueid) {
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
    CIsoSurface* isosurface_var = (CIsoSurface*)obj;

    switch (valueid) {
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
    CIsoSurface* isosurface_var = (CIsoSurface*)obj;

    switch (valueid) {
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
    CIsoSurface* thisobj = (CIsoSurface*)obj;
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
bool CIsoSurface::DefaultSigHandler(tSig *sig) {
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
tMsg* CIsoSurface::DefaultMsgHandler(tMsg *msg) {
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
    CIsoSurface* thisobj = (CIsoSurface*)obj;

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
    CIsoSurface*thisobj=(CIsoSurface*)obj;
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
//  Method-Name   : create_isosurface_obj()
//
//  Generated source code.
//
// **************************************************************************
static tSimObj* create_isosurface_obj(objectid_t  oid) {
    CIsoSurface* newisosurface = new CIsoSurface;

    if (newisosurface != 0) {
        tSimObj* newobj = newisosurface;

        newobj->type        = IDO_ISOSURFACE;
        newobj->objid       = oid;
        newobj->parent      = 0;
        newobj->setvalue    = setvalue;
        newobj->getvalue    = getvalue;
        newobj->save        = save;
        newobj->update      = init_object;
        newobj->process     = process_sig;
        newobj->syncprocess = process_msg;
        if (0xc0000000 & oid) {
            t_store.insert(std::pair<templateid_t, CIsoSurface*>(oid, newisosurface));
        }
    } else {
    }
    return ((tSimObj*)newisosurface);
}
// **************************************************************************
//
//  Method-Name   : create_new_isosurface_obj()
//
//  Generated source code.
//
// **************************************************************************
static tSimObj* create_new_isosurface_obj(objectid_t  oid) {
    CIsoSurface* newisosurface = new CIsoSurface;

    if (newisosurface != 0) {
        tSimObj* newobj = newisosurface;

        newobj->type        = IDO_ISOSURFACE;
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
        stdb_createobj(oid, IDO_ISOSURFACE);
        //
        //  Now fill the attributes with values.
        //
        //  create the attribute data in the DB.
    } else {
    }
    return ((tSimObj*)newisosurface);
}
// **************************************************************************
//
//  Method-Name   : create_new_isosurface_obj_from_template()
//
//  Generated source code.
//
// **************************************************************************
static tSimObj* create_new_isosurface_obj_from_template(templateid_t  tid, objectid_t  oid) {
    CIsoSurface* newisosurface = 0;
    std::map<objectid_t, CIsoSurface*>::iterator found;

    found = t_store.find(tid);
    if (found != t_store.end()) {
        newisosurface = new CIsoSurface;
        if (newisosurface != 0) {
            tSimObj* newobj = newisosurface;

            newobj->type        = IDO_ISOSURFACE;
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
            stdb_createobj(oid, IDO_ISOSURFACE);
            //
            //
            //  Copy data from template.
            //
        } else {
        }
    } else {
    }
    return ((tSimObj*)newisosurface);
}

tObjLib isosurface_factory= {0, 0, 0, IDO_ISOSURFACE, create_isosurface_obj, create_new_isosurface_obj, create_new_isosurface_obj_from_template};
