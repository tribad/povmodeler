// *************************************************************************************************************
//
//  Modul-Name     : tMsgEndCycleReq.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
// HOC *********************************************************************************************************
//          |         |
// YYYYMMDD | Creator | description
//--------------------------------------------------------------------------------------------------------------
//          |         |
//----------+---------+-----------------------------------------------------------------------------------------
//          |         |
// HOC end *****************************************************************************************************
#pragma once
#ifndef TMSGENDCYCLEREQ_INC
#define TMSGENDCYCLEREQ_INC

#define IDM_ENDCYCLEREQ (0x516f21340e54ede9)
#if (SIMVERSION == 1)
typedef struct tagMsgEndCycleReq {
#else
struct tMsgEndCycleReq : public tMsg {
#endif
    tMsgEndCycleReq() {id = IDM_ENDCYCLEREQ;type = MSG_TYPE_REQUEST | MSG_TYPE_INTERNAL;}
    tMsgEndCycleReq(tJSON* j)  {(void)j; id = IDM_ENDCYCLEREQ;type = MSG_TYPE_REQUEST | MSG_TYPE_INTERNAL;}
    virtual ~tMsgEndCycleReq() {}
    uint64_t    Cycle;
};

#endif  // TMSGENDCYCLEREQ_INC
