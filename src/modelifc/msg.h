// **************************************************************************
//
//  Modul-Name     : msg.h
//  Author(s)      : Hans-Juergen Lange
//
//  Copyrights 2014 by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
#ifndef MSG_H
#define MSG_H

#define MSG_TYPE_REQUEST    0x0000000000000001
#define MSG_TYPE_REPLY      0x0000000000000002
#define MSG_TYPE_INDICATION 0x0000000000000004
#define MSG_TYPE_CONFIRM    0x0000000000000008
#define MSG_TYPE_INTERNAL   0x1000000000000000
#define MSG_TYPE_SIGNAL     0x2000000000000000

#include <iostream>
#include <json.h>
#include <commtarget.h>

/*
 * The message type.
 */
struct tMsg {
    tMsg(uint64_t aId = 0u, uint64_t aType = MSG_TYPE_INTERNAL) {id = aId; type = aType;}
    tMsg(tJSON* aJson) {id = 0; type = MSG_TYPE_INTERNAL; (void)aJson;}
    virtual ~tMsg() {}
    virtual std::ostream& json(std::ostream& output) {return output;}
    uint64_t    id;
    uint64_t    type;
    tCommTarget src;
    tCommTarget dst;
};

using tSig = tMsg;

#endif // MSG_H
