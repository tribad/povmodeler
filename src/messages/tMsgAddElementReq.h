// *************************************************************************************************************
//
//  Modul-Name     : tMsgAddElementReq.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef TMSGADDELEMENTREQ_INC
#define TMSGADDELEMENTREQ_INC

#include <simobj.h>
#include <helper.h>

#define IDM_ADDELEMENTREQ 0x24309728bddfea8e
//
//                   M e s s a g e c l a s s     d e c l a r a t i o n
struct tMsgAddElementReq : public tMsg {
    tMsgAddElementReq() { id = IDM_ADDELEMENTREQ; type = MSG_TYPE_REQUEST;}
    tMsgAddElementReq(const tCommTarget& aDst, const tCommTarget& aSrc) {
        id = IDM_ADDELEMENTREQ; 
        type = MSG_TYPE_REQUEST;
        src = aSrc;
        dst = aDst;
    }
    tMsgAddElementReq(tSimObj* aDst, tSimObj* aSrc) {
        id          = IDM_ADDELEMENTREQ; 
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
    tMsgAddElementReq(tJSON* json) {
        id          = IDM_ADDELEMENTREQ; 
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
    virtual ~tMsgAddElementReq() {}
    virtual std::ostream& json(std::ostream& output) {
        output << "\"MsgId\": \"AddElementReq\"";

        return output;
    }
};

#endif  // TMSGADDELEMENTREQ_INC
