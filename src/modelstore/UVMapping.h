// *************************************************************************************************************
//
//  Modul-Name     : UVMapping.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef UVMAPPING_INC
#define UVMAPPING_INC
//
//  Forward declarations
//
//                   S i m o b j e c t    d e c l a r a t i o n
struct UVMapping : public tSimObj {
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

extern tObjLib uvmapping_factory;

#endif  // UVMAPPING_INC
