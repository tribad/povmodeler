// *************************************************************************************************************
//
//  Modul-Name     : tMsgStartImportReply.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef TMSGSTARTIMPORTREPLY_INC
#define TMSGSTARTIMPORTREPLY_INC

#include <simobj.h>
#include <helper.h>
#include <string>
#include <stdint.h>

#define IDM_STARTIMPORTREPLY 0xfbfa1a026615a839
//
//                   M e s s a g e c l a s s     d e c l a r a t i o n
struct tMsgStartImportReply : public tMsg {
    tMsgStartImportReply() { id = IDM_STARTIMPORTREPLY; type = MSG_TYPE_REPLY;}
    tMsgStartImportReply(const tCommTarget& aDst, const tCommTarget& aSrc) {
        id = IDM_STARTIMPORTREPLY; 
        type = MSG_TYPE_REPLY;
        src = aSrc;
        dst = aDst;
    }
    tMsgStartImportReply(tSimObj* aDst, tSimObj* aSrc) {
        id          = IDM_STARTIMPORTREPLY; 
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
    tMsgStartImportReply(tJSON* json) {
        id          = IDM_STARTIMPORTREPLY; 
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
            j=find(json, "FileName");
            if (j!=0) {
                FileName=to_string(j);
            }
            j=find(json, "ProjectId");
            if (j!=0) {
                ProjectId=to_uint64_t(j);
            }
        }
    }
    virtual ~tMsgStartImportReply() {}
    virtual std::ostream& json(std::ostream& output) {
        output << "\"MsgId\": \"StartImportReply\"";
        output <<  ", \"FileName\":\"" << helper::escape(this->FileName) << "\"";
        output <<  ", \"ProjectId\":" << (int64_t)this->ProjectId;

        return output;
    }
    std::string FileName;
    uint64_t    ProjectId;
};

#endif  // TMSGSTARTIMPORTREPLY_INC
