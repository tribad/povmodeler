// *************************************************************************************************************
//
//  Modul-Name     : tMsgEndImportReply.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef TMSGENDIMPORTREPLY_INC
#define TMSGENDIMPORTREPLY_INC

#include <simobj.h>
#include <helper.h>

#define IDM_ENDIMPORTREPLY 0x123f567aa043f490
//
//                   M e s s a g e c l a s s     d e c l a r a t i o n
struct tMsgEndImportReply : public tMsg {
    tMsgEndImportReply() { id = IDM_ENDIMPORTREPLY; type = MSG_TYPE_REPLY;}
    tMsgEndImportReply(const tCommTarget& aDst, const tCommTarget& aSrc) {
        id = IDM_ENDIMPORTREPLY; 
        type = MSG_TYPE_REPLY;
        src = aSrc;
        dst = aDst;
    }
    tMsgEndImportReply(tSimObj* aDst, tSimObj* aSrc) {
        id          = IDM_ENDIMPORTREPLY; 
        type        = MSG_TYPE_REPLY;
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
    tMsgEndImportReply(tJSON* json) {
        id          = IDM_ENDIMPORTREPLY; 
        type        = MSG_TYPE_REPLY;
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
    virtual ~tMsgEndImportReply() {}
    virtual std::ostream& json(std::ostream& output) {
        output << "\"MsgId\": \"EndImportReply\"";

        return output;
    }
};

#endif  // TMSGENDIMPORTREPLY_INC
