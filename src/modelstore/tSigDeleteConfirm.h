#pragma once
#ifndef TSIGDELETECONFIRM_INC
#define TSIGDELETECONFIRM_INC

#define IDS_DELETECONFIRM 0x0ad4c4c4f299ff5f

//
//               M e s s a g e c l a s s     d e c l a r a t i o n
typedef struct __tSigDeleteConfirm {
    uint64_t   id;
    void*      src;
    void*      dst;
    uint64_t   type;
} tSigDeleteConfirm;

#endif
