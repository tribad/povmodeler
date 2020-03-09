// *************************************************************************************************************
//
//  Modul-Name     : _simifc.cpp
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#include <simifc.h>
#include <stdint.h>
#include <stdlib.h>
#include <simobjfactory.h>
#include <simapi.h>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#ifdef __linux__
#include <pthread.h>
#endif
#include <set>
#include <pointerindex.h>
#include <helper.h>
#include "generated.h"
#include "ids.h"
#include "tMsgDeleteReq.h"
#include "tMsgDeleteReply.h"
#include "tSigDeleteIndication.h"
#include "tSigDeleteConfirm.h"
#include <tMsgStartCycleReq.h>
#include <tMsgEndCycleReq.h>
#include <tMsgInvalidReply.h>
#include <tSigInvalidIndication.h>
//
//                       M o d e l   i n c l u d e s

#include "CObjectBase.h"
#include "CProject.h"
//
//            S t a t i c   F u n c t i o n    p r o t o t y p e s
//
//
typedef tMsg*  (*msg_from_json_op)(tJSON*);
typedef std::ostream& (*msg_to_json_op)(tMsg*, std::ostream&);
typedef tSig*  (*sig_from_json_op)(tJSON*);
typedef std::ostream& (*sig_to_json_op)(tSig*, std::ostream&);

class CGeneratedSimIfc : public CSimIfc {
public:
    CGeneratedSimIfc() {
        mainviewport = 0;

        addsimobjfactory(&project_factory);
}
    virtual ~CGeneratedSimIfc() {}
    virtual int       CreateObject(uint64_t oid, uint64_t tid);
    virtual void      SetValue(uint64_t oid, uint64_t vid, uint64_t vidx, const tVariant& value);
    virtual void      StartCycle();
    virtual void      EndCycle();
    virtual tMsg*     Process(tMsg* aMsg);
    virtual tMsg*     Process(tCommTarget& src, tJSON* aJson);
    virtual tNetPack* Process(tNetPack* aPackage);
    virtual tNetPack* ProcessRaw(tNetPack* aPackage);
private:
    tSimObj*                                mainviewport;
    std::map<std::string, sig_from_json_op> sigfrommap;
    std::map<uint64_t,    sig_to_json_op>   sigtomap;
    std::map<std::string, msg_from_json_op> msgfrommap;
    std::map<uint64_t, msg_to_json_op>      msgtomap;
    std::map<templateid_t, tSimObj*>        templatemap;
};

int CGeneratedSimIfc::CreateObject(uint64_t oid, uint64_t tid) {
   /*
    * We are passing the oid with the creation function into the object.
    * This way we can filter the templates and store them into the object module
    */
   tSimObj* newobj=factory_createobj(tid, oid);
   /*
    * If the object could be created from the type id the loading
    * can proceed.
    */
   if (newobj!=0) {
       /*
        * The top two bits are used for templates and other stuff only.
        * They must be created but not added to the simulation loop or the
        * idmap.
        */
       if ((oid&0xc0000000)==0) {
           simidx.Add(newobj);
           StartObject(newobj);
       } else {
           templatemap.insert(std::pair<objectid_t, tSimObj*>(oid, newobj));
       }
        if (oid == 0) {
            mainviewport = newobj;
        }
   }
   return (newobj!=0);
}
void      CGeneratedSimIfc::SetValue(uint64_t oid, uint64_t vid, uint64_t vidx, const tVariant& value) {
    tSimObj* obj = simidx.Find(oid);
    if (obj != 0) {
        ::SetValue(obj, vid, vidx, value);
    }
}
void      CGeneratedSimIfc::StartCycle() {
    tMsgStartCycleReq s;

    s.id    = IDM_STARTCYCLEREQ;
    s.Cycle = GetCycle();
    if (mainviewport != 0) {
        mainviewport->syncprocess(mainviewport, (tMsg*)&s);
    }
}
void      CGeneratedSimIfc::EndCycle() {
    tMsgEndCycleReq s;

    s.id    = IDM_ENDCYCLEREQ;
    s.Cycle = GetCycle();
    if (mainviewport != 0) {
        mainviewport->syncprocess(mainviewport, (tMsg*)&s);
    }
}
tMsg*     CGeneratedSimIfc::Process(tMsg* aMsg) {
    tMsg* retval =0;

    if (aMsg->dst.obj.id == 0) {
        aMsg->dst.obj.ptr = mainviewport;
    } else {
        aMsg->dst.obj.ptr = simidx.Find(aMsg->dst.obj.id);
    }
    if (aMsg->dst.obj.ptr != 0) {
        if (aMsg->type & MSG_TYPE_SIGNAL) {
            SendSig((tSimObj*)(aMsg->dst.obj.ptr), aMsg);
        } else {
            retval = SendMsg((tSimObj*)(aMsg->dst.obj.ptr), aMsg);
        }
    }
    return retval;
}
tMsg* CGeneratedSimIfc::Process(tCommTarget& src, tJSON* aJson) {
    tMsg* retval = nullptr;
    if (aJson != 0) {
         tJSON* j   = find(aJson, "MsgId");

         if (j != 0) {
             tMsg*       msg = 0;
             std::string id  = helper::tolower( ((tJSONValue*)(j))->value );

             {
             }
             if (msg != 0) {
                 msg->src = src;
                 if (msg->dst.obj.id == 0) {
                     msg->dst.obj.ptr = mainviewport;
                 } else {
                     msg->dst.obj.ptr = simidx.Find(msg->dst.obj.id);
                 }
                 if (msg->dst.obj.ptr != 0) {
                     msg = SendMsg((tSimObj*)(msg->dst.obj.ptr), msg);
                 }
                 retval = msg;
             } else {
                 tMsgInvalidReply* invalid = new tMsgInvalidReply;

                 invalid->dst = src;
                 invalid->MsgName = (std::string) ( ((tJSONValue*)(j))->value );
                 retval = invalid;
             }
         } else {
             j = find(aJson, "SignalId");
             if (j != 0) {
                 tSig*       sig = 0;
                 std::string id = helper::tolower( ((tJSONValue*)(j))->value );

                 {
                 }
                 if (sig != 0) {
                     sig->src = src;
                     if (sig->dst.obj.id == 0) {
                         sig->dst.obj.ptr = mainviewport;
                     } else {
                         sig->dst.obj.ptr = simidx.Find(sig->dst.obj.id);
                     }
                     if (sig->dst.obj.ptr != 0) {
                         SendSig((tSimObj*)(sig->dst.obj.ptr), sig);
                     }
                 } else {
                     tSigInvalidIndication* invalid = new tSigInvalidIndication;

                     invalid->dst = src;
                     invalid->SignalName = (std::string) ( ((tJSONValue*)(j))->value );
                     SendSig(invalid);
                }
             }
         }
    }
    return retval;
}
tNetPack* CGeneratedSimIfc::Process(tNetPack* aPackage) {
    return 0;
}
tNetPack* CGeneratedSimIfc::ProcessRaw(tNetPack* aPackage) {
    return 0;
}
CGeneratedSimIfc simifc;
// **************************************************************************
//
//  Method-Name   : siminit()
//
//  Generated source code.
//
// **************************************************************************
CSimIfc* siminit(void) {
    //
    //  Create the main viewport object CProject
    simifc.CreateObject(0ul, IDO_PROJECT);
    return &simifc;
}
