#pragma once
#ifndef TSIGDELETEINDICATION_INC
#define TSIGDELETEINDICATION_INC

#define IDS_DELETEINDICATION 0xf232c1f988f9e0b7

//
//               M e s s a g e c l a s s     d e c l a r a t i o n
typedef struct __tSigDeleteIndication {
    uint64_t   id;
    void*      src;
    void*      dst;
    uint64_t   type;
} tSigDeleteIndication;

#endif
