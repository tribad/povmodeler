// *************************************************************************************************************
//
//  Modul-Name     : tMsgAddElementReply.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef TMSGADDELEMENTREPLY_INC
#define TMSGADDELEMENTREPLY_INC

#include <simobj.h>
#include <helper.h>

#define IDM_ADDELEMENTREPLY 0x358325131ea8024b
//
//                   M e s s a g e c l a s s     d e c l a r a t i o n
struct tMsgAddElementReply : public tMsg {
    tMsgAddElementReply() { id = IDM_ADDELEMENTREPLY; type = MSG_TYPE_REPLY;}
    tMsgAddElementReply(const tCommTarget& aDst, const tCommTarget& aSrc) {
        id = IDM_ADDELEMENTREPLY; 
        type = MSG_TYPE_REPLY;
        src = aSrc;
        dst = aDst;
    }
    tMsgAddElementReply(tSimObj* aDst, tSimObj* aSrc) {
        id          = IDM_ADDELEMENTREPLY; 
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
    tMsgAddElementReply(tJSON* json) {
        id          = IDM_ADDELEMENTREPLY; 
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
            j=find(json, "Error");
            if (j!=0) {
                Error=to_int(j);
            }
        }
    }
    virtual ~tMsgAddElementReply() {}
    virtual std::ostream& json(std::ostream& output) {
        output << "\"MsgId\": \"AddElementReply\"";
        output <<  ", \"Error\":" << this->Error;

        return output;
    }
    int Error;
};

#endif  // TMSGADDELEMENTREPLY_INC
