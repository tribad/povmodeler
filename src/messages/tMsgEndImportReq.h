// *************************************************************************************************************
//
//  Modul-Name     : tMsgEndImportReq.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef TMSGENDIMPORTREQ_INC
#define TMSGENDIMPORTREQ_INC

#include <simobj.h>
#include <helper.h>

#define IDM_ENDIMPORTREQ 0x5ec12905be0ffb3b
//
//                   M e s s a g e c l a s s     d e c l a r a t i o n
struct tMsgEndImportReq : public tMsg {
    tMsgEndImportReq() { id = IDM_ENDIMPORTREQ; type = MSG_TYPE_REQUEST;}
    tMsgEndImportReq(const tCommTarget& aDst, const tCommTarget& aSrc) {
        id = IDM_ENDIMPORTREQ; 
        type = MSG_TYPE_REQUEST;
        src = aSrc;
        dst = aDst;
    }
    tMsgEndImportReq(tSimObj* aDst, tSimObj* aSrc) {
        id          = IDM_ENDIMPORTREQ; 
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
    tMsgEndImportReq(tJSON* json) {
        id          = IDM_ENDIMPORTREQ; 
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
    virtual ~tMsgEndImportReq() {}
    virtual std::ostream& json(std::ostream& output) {
        output << "\"MsgId\": \"EndImportReq\"";

        return output;
    }
};

#endif  // TMSGENDIMPORTREQ_INC
