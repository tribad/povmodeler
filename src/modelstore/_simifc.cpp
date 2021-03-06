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
#include "tMsgStartImportReq.h"
#include "tMsgStartImportReply.h"
#include "tMsgEndImportReq.h"
#include "tMsgEndImportReply.h"
#include "tMsgAddElementReq.h"
#include "tMsgAddElementReply.h"

#include "CObjectBase.h"
#include "CMainViewport.h"
#include "CProject.h"
#include "CScene.h"
#include "CCamera.h"
#include "CLightSource.h"
#include "CLightGroup.h"
#include "CBlob.h"
#include "CBox.h"
#include "CCone.h"
#include "CCylinder.h"
#include "CHeightField.h"
#include "CIsoSurface.h"
#include "CJuliaFractal.h"
#include "CLathe.h"
#include "COvus.h"
#include "CParametric.h"
#include "CPrism.h"
#include "CSphere.h"
#include "CSphereSweep.h"
#include "CSuperQuadricElipsoid.h"
#include "CSurfaceOfRevolution.h"
#include "CText.h"
#include "CTorus.h"
#include "CBicubicPatch.h"
#include "CDisc.h"
#include "CMesh.h"
#include "CMesh2.h"
#include "CPolygon.h"
#include "CTriangle.h"
#include "CSmoothTriangle.h"
#include "CUnion.h"
#include "CIntersection.h"
#include "CDifference.h"
#include "CMerge.h"
#include "CPigment.h"
#include "CNormal.h"
#include "CFinish.h"
#include "CHalo.h"
#include "CPatternedTexture.h"
#include "UVMapping.h"
#include "CTexture.h"
//
//            S t a t i c   F u n c t i o n    p r o t o t y p e s
//
//
static tMsg* msg_from_json_startimportreq(tJSON*  json);
static std::ostream& msg_to_json_startimportreq(tMsg* aMsg, std::ostream& output);
static tMsg* msg_from_json_startimportreply(tJSON*  json);
static std::ostream& msg_to_json_startimportreply(tMsg* aMsg, std::ostream& output);
static tMsg* msg_from_json_endimportreq(tJSON*  json);
static std::ostream& msg_to_json_endimportreq(tMsg* aMsg, std::ostream& output);
static tMsg* msg_from_json_endimportreply(tJSON*  json);
static std::ostream& msg_to_json_endimportreply(tMsg* aMsg, std::ostream& output);
static tMsg* msg_from_json_addelementreq(tJSON*  json);
static std::ostream& msg_to_json_addelementreq(tMsg* aMsg, std::ostream& output);
static tMsg* msg_from_json_addelementreply(tJSON*  json);
static std::ostream& msg_to_json_addelementreply(tMsg* aMsg, std::ostream& output);
typedef tMsg*  (*msg_from_json_op)(tJSON*);
typedef std::ostream& (*msg_to_json_op)(tMsg*, std::ostream&);
typedef tSig*  (*sig_from_json_op)(tJSON*);
typedef std::ostream& (*sig_to_json_op)(tSig*, std::ostream&);

class CGeneratedSimIfc : public CSimIfc {
public:
    CGeneratedSimIfc() {
        mainviewport = 0;
        msgfrommap.insert(std::pair<std::string, msg_from_json_op>("startimportreq", msg_from_json_startimportreq));
        msgtomap.insert(std::pair<uint64_t, msg_to_json_op>(IDM_STARTIMPORTREQ, msg_to_json_startimportreq));
        msgfrommap.insert(std::pair<std::string, msg_from_json_op>("startimportreply", msg_from_json_startimportreply));
        msgtomap.insert(std::pair<uint64_t, msg_to_json_op>(IDM_STARTIMPORTREPLY, msg_to_json_startimportreply));
        msgfrommap.insert(std::pair<std::string, msg_from_json_op>("endimportreq", msg_from_json_endimportreq));
        msgtomap.insert(std::pair<uint64_t, msg_to_json_op>(IDM_ENDIMPORTREQ, msg_to_json_endimportreq));
        msgfrommap.insert(std::pair<std::string, msg_from_json_op>("endimportreply", msg_from_json_endimportreply));
        msgtomap.insert(std::pair<uint64_t, msg_to_json_op>(IDM_ENDIMPORTREPLY, msg_to_json_endimportreply));
        msgfrommap.insert(std::pair<std::string, msg_from_json_op>("addelementreq", msg_from_json_addelementreq));
        msgtomap.insert(std::pair<uint64_t, msg_to_json_op>(IDM_ADDELEMENTREQ, msg_to_json_addelementreq));
        msgfrommap.insert(std::pair<std::string, msg_from_json_op>("addelementreply", msg_from_json_addelementreply));
        msgtomap.insert(std::pair<uint64_t, msg_to_json_op>(IDM_ADDELEMENTREPLY, msg_to_json_addelementreply));

        addsimobjfactory(&objectbase_factory);
        addsimobjfactory(&mainviewport_factory);
        addsimobjfactory(&project_factory);
        addsimobjfactory(&scene_factory);
        addsimobjfactory(&camera_factory);
        addsimobjfactory(&lightsource_factory);
        addsimobjfactory(&lightgroup_factory);
        addsimobjfactory(&blob_factory);
        addsimobjfactory(&box_factory);
        addsimobjfactory(&cone_factory);
        addsimobjfactory(&cylinder_factory);
        addsimobjfactory(&heightfield_factory);
        addsimobjfactory(&isosurface_factory);
        addsimobjfactory(&juliafractal_factory);
        addsimobjfactory(&lathe_factory);
        addsimobjfactory(&ovus_factory);
        addsimobjfactory(&parametric_factory);
        addsimobjfactory(&prism_factory);
        addsimobjfactory(&sphere_factory);
        addsimobjfactory(&spheresweap_factory);
        addsimobjfactory(&superquadricelipsoid_factory);
        addsimobjfactory(&surfaceofrevolution_factory);
        addsimobjfactory(&text_factory);
        addsimobjfactory(&torus_factory);
        addsimobjfactory(&bicubicpatch_factory);
        addsimobjfactory(&disc_factory);
        addsimobjfactory(&mesh_factory);
        addsimobjfactory(&mesh2_factory);
        addsimobjfactory(&polygon_factory);
        addsimobjfactory(&triangle_factory);
        addsimobjfactory(&smoothtriangle_factory);
        addsimobjfactory(&union_factory);
        addsimobjfactory(&intersection_factory);
        addsimobjfactory(&difference_factory);
        addsimobjfactory(&merge_factory);
        addsimobjfactory(&pigment_factory);
        addsimobjfactory(&normal_factory);
        addsimobjfactory(&finish_factory);
        addsimobjfactory(&halo_factory);
        addsimobjfactory(&patternedtexture_factory);
        addsimobjfactory(&uvmapping_factory);
        addsimobjfactory(&texture_factory);
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
public:
    tSimObj*                                mainviewport;
private:
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

             if (id == "startimportreq") {
                 msg = new tMsgStartImportReq(aJson);
             } else if (id == "startimportreply") {
                 msg = new tMsgStartImportReply(aJson);
             } else if (id == "endimportreq") {
                 msg = new tMsgEndImportReq(aJson);
             } else if (id == "endimportreply") {
                 msg = new tMsgEndImportReply(aJson);
             } else if (id == "addelementreq") {
                 msg = new tMsgAddElementReq(aJson);
             } else if (id == "addelementreply") {
                 msg = new tMsgAddElementReply(aJson);
             } else {
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
//  Method-Name   : msg_from_json_startimportreq()
//
//  Generated source code.
//
// **************************************************************************
static tMsg* msg_from_json_startimportreq(tJSON*  json) {
    tMsgStartImportReq* newsig = new tMsgStartImportReq;
    tJSON *j;

    j=find(json, "Destination");
    if (j != 0) {
        newsig->dst.obj.id  = to_objectid_t(j);
    } else {
        newsig->dst.obj.id  = 0;
    }
    newsig->dst.type    = eCommTarget::Object;
    newsig->dst.obj.ptr = simidx.Find(newsig->dst.obj.id);
    j=find(json, "FileName");
    if (j!=0) {
        newsig->FileName=to_string(j);
    }
    return ((tMsg*)(newsig));
}
// **************************************************************************
//
//  Method-Name   : msg_to_json_startimportreq()
//
//  Generated source code.
//
// **************************************************************************
static std::ostream& msg_to_json_startimportreq(tMsg* aMsg, std::ostream& output) {
    tMsgStartImportReq* msg=(tMsgStartImportReq*)aMsg;
    output << "\"MsgId\": \"StartImportReq\"";
    output <<  ", \"FileName\":\"" << helper::escape(msg->FileName) << "\"";
    return (output);
}
// **************************************************************************
//
//  Method-Name   : msg_from_json_startimportreply()
//
//  Generated source code.
//
// **************************************************************************
static tMsg* msg_from_json_startimportreply(tJSON*  json) {
    tMsgStartImportReply* newsig = new tMsgStartImportReply;
    tJSON *j;

    j=find(json, "Destination");
    if (j != 0) {
        newsig->dst.obj.id  = to_objectid_t(j);
    } else {
        newsig->dst.obj.id  = 0;
    }
    newsig->dst.type    = eCommTarget::Object;
    newsig->dst.obj.ptr = simidx.Find(newsig->dst.obj.id);
    j=find(json, "FileName");
    if (j!=0) {
        newsig->FileName=to_string(j);
    }
    j=find(json, "ProjectId");
    if (j!=0) {
        newsig->ProjectId=to_uint64_t(j);
    }
    return ((tMsg*)(newsig));
}
// **************************************************************************
//
//  Method-Name   : msg_to_json_startimportreply()
//
//  Generated source code.
//
// **************************************************************************
static std::ostream& msg_to_json_startimportreply(tMsg* aMsg, std::ostream& output) {
    tMsgStartImportReply* msg=(tMsgStartImportReply*)aMsg;
    output << "\"MsgId\": \"StartImportReply\"";
    output <<  ", \"FileName\":\"" << helper::escape(msg->FileName) << "\"";
    output <<  ", \"ProjectId\":" << (int64_t)msg->ProjectId;
    return (output);
}
// **************************************************************************
//
//  Method-Name   : msg_from_json_endimportreq()
//
//  Generated source code.
//
// **************************************************************************
static tMsg* msg_from_json_endimportreq(tJSON*  json) {
    tMsgEndImportReq* newsig = new tMsgEndImportReq;
    tJSON *j;

    j=find(json, "Destination");
    if (j != 0) {
        newsig->dst.obj.id  = to_objectid_t(j);
    } else {
        newsig->dst.obj.id  = 0;
    }
    newsig->dst.type    = eCommTarget::Object;
    newsig->dst.obj.ptr = simidx.Find(newsig->dst.obj.id);
    return ((tMsg*)(newsig));
}
// **************************************************************************
//
//  Method-Name   : msg_to_json_endimportreq()
//
//  Generated source code.
//
// **************************************************************************
static std::ostream& msg_to_json_endimportreq(tMsg* aMsg, std::ostream& output) {
    tMsgEndImportReq* msg=(tMsgEndImportReq*)aMsg;
    output << "\"MsgId\": \"EndImportReq\"";
    return (output);
}
// **************************************************************************
//
//  Method-Name   : msg_from_json_endimportreply()
//
//  Generated source code.
//
// **************************************************************************
static tMsg* msg_from_json_endimportreply(tJSON*  json) {
    tMsgEndImportReply* newsig = new tMsgEndImportReply;
    tJSON *j;

    j=find(json, "Destination");
    if (j != 0) {
        newsig->dst.obj.id  = to_objectid_t(j);
    } else {
        newsig->dst.obj.id  = 0;
    }
    newsig->dst.type    = eCommTarget::Object;
    newsig->dst.obj.ptr = simidx.Find(newsig->dst.obj.id);
    return ((tMsg*)(newsig));
}
// **************************************************************************
//
//  Method-Name   : msg_to_json_endimportreply()
//
//  Generated source code.
//
// **************************************************************************
static std::ostream& msg_to_json_endimportreply(tMsg* aMsg, std::ostream& output) {
    tMsgEndImportReply* msg=(tMsgEndImportReply*)aMsg;
    output << "\"MsgId\": \"EndImportReply\"";
    return (output);
}
// **************************************************************************
//
//  Method-Name   : msg_from_json_addelementreq()
//
//  Generated source code.
//
// **************************************************************************
static tMsg* msg_from_json_addelementreq(tJSON*  json) {
    tMsgAddElementReq* newsig = new tMsgAddElementReq;
    tJSON *j;

    j=find(json, "Destination");
    if (j != 0) {
        newsig->dst.obj.id  = to_objectid_t(j);
    } else {
        newsig->dst.obj.id  = 0;
    }
    newsig->dst.type    = eCommTarget::Object;
    newsig->dst.obj.ptr = simidx.Find(newsig->dst.obj.id);
    return ((tMsg*)(newsig));
}
// **************************************************************************
//
//  Method-Name   : msg_to_json_addelementreq()
//
//  Generated source code.
//
// **************************************************************************
static std::ostream& msg_to_json_addelementreq(tMsg* aMsg, std::ostream& output) {
    tMsgAddElementReq* msg=(tMsgAddElementReq*)aMsg;
    output << "\"MsgId\": \"AddElementReq\"";
    return (output);
}
// **************************************************************************
//
//  Method-Name   : msg_from_json_addelementreply()
//
//  Generated source code.
//
// **************************************************************************
static tMsg* msg_from_json_addelementreply(tJSON*  json) {
    tMsgAddElementReply* newsig = new tMsgAddElementReply;
    tJSON *j;

    j=find(json, "Destination");
    if (j != 0) {
        newsig->dst.obj.id  = to_objectid_t(j);
    } else {
        newsig->dst.obj.id  = 0;
    }
    newsig->dst.type    = eCommTarget::Object;
    newsig->dst.obj.ptr = simidx.Find(newsig->dst.obj.id);
    return ((tMsg*)(newsig));
}
// **************************************************************************
//
//  Method-Name   : msg_to_json_addelementreply()
//
//  Generated source code.
//
// **************************************************************************
static std::ostream& msg_to_json_addelementreply(tMsg* aMsg, std::ostream& output) {
    tMsgAddElementReply* msg=(tMsgAddElementReply*)aMsg;
    output << "\"MsgId\": \"AddElementReply\"";
    return (output);
}
// **************************************************************************
//
//  Method-Name   : siminit()
//
//  Generated source code.
//
// **************************************************************************
CSimIfc* siminit(void) {
    //
    //  Create the main viewport object CMainViewport
    simifc.CreateObject(0ul, IDO_MAINVIEWPORT);
    if (simifc.mainviewport != nullptr) {
        simifc.mainviewport->update(simifc.mainviewport, 0u);
    }
    return &simifc;
}
