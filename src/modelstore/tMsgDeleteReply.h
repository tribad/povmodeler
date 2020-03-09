#pragma once
#ifndef TMSGDELETEREPLY_INC
#define TMSGDELETEREPLY_INC

#define IDM_DELETEREPLY 0x17d5182ebfb740fc

//
//               M e s s a g e c l a s s     d e c l a r a t i o n
typedef struct __tMsgDeleteReply {
    uint64_t   id;
    void*      src;
    void*      dst;
    uint64_t   type;
} tMsgDeleteReply;

#endif
