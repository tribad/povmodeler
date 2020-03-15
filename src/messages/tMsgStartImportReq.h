// *************************************************************************************************************
//
//  Modul-Name     : tMsgStartImportReq.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef TMSGSTARTIMPORTREQ_INC
#define TMSGSTARTIMPORTREQ_INC

#include <simobj.h>
#include <helper.h>

#define IDM_STARTIMPORTREQ 0xadbad44c9df6819e
//
//                   M e s s a g e c l a s s     d e c l a r a t i o n
struct tMsgStartImportReq : public tMsg {
    tMsgStartImportReq() { id = IDM_STARTIMPORTREQ; type = MSG_TYPE_REQUEST;}
    tMsgStartImportReq(const tCommTarget& aDst, const tCommTarget& aSrc) {
        id = IDM_STARTIMPORTREQ; 
        type = MSG_TYPE_REQUEST;
        src = aSrc;
        dst = aDst;
    }
    tMsgStartImportReq(tSimObj* aDst, tSimObj* aSrc) {
        id          = IDM_STARTIMPORTREQ; 
        type        = MSG_TYPE_REQUEST;
        if (aSrc != 0) {
            src.type    = eCommTarget::Object;
            src.obj.id  = aSrc->objid;
            src.obj.ptr = aSrc;
        } else {
            src.type    = eCommTarget::Unknown;
            src.obj.id  = 0;
            src.obj.ptr = 0;
        }
        if (aDst != 0) {
            dst.type    = eCommTarget::Object;
            dst.obj.id  = aDst->objid;
            dst.obj.ptr = aDst;
        } else {
            src.type    = eCommTarget::Unknown;
            src.obj.id  = 0;
            src.obj.ptr = 0;
        }
    }
    tMsgStartImportReq(tJSON* json) {
        id          = IDM_STARTIMPORTREQ; 
        type        = MSG_TYPE_REQUEST;
        if (json != 0) {
            tJSON *j;

            j=find(json, "Destination");
            if (j != 0) {
                dst.obj.id  = ((tJSONValue*)(j))->value;
            } else {
                dst.obj.id  = 0;
            }
            dst.type    = eCommTarget::Object;
        }
    }
    virtual ~tMsgStartImportReq() {}
    virtual std::ostream& json(std::ostream& output) {
        output << "\"MsgId\": \"StartImportReq\"";

        return output;
    }
};

#endif  // TMSGSTARTIMPORTREQ_INC
