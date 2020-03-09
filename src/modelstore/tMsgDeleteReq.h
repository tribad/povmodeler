#pragma once
#ifndef TMSGDELETEREQ_INC
#define TMSGDELETEREQ_INC

#define IDM_DELETEREQ 0x46e9e6ccb03295eb

//
//               M e s s a g e c l a s s     d e c l a r a t i o n
typedef struct __tMsgDeleteReq {
    uint64_t   id;
    void*      src;
    void*      dst;
    uint64_t   type;
} tMsgDeleteReq;

#endif
