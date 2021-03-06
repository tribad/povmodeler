// *************************************************************************************************************
//
//  Modul-Name     : COvus.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef OVUS_INC
#define OVUS_INC
//
//  Forward declarations
//
//                   S i m o b j e c t    d e c l a r a t i o n
struct COvus : public tSimObj {
    /*
     *  These are the message and signal processing functions.
     */
public:
    tMsg* DefaultMsgHandler(tMsg* aMsg);
    bool  DefaultSigHandler(tSig* aSignal);
    /*
     *  Here are the attributes of the object defined.
     */
public:
};

extern tObjLib ovus_factory;

#endif  // OVUS_INC
