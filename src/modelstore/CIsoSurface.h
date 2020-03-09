// *************************************************************************************************************
//
//  Modul-Name     : CIsoSurface.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef ISOSURFACE_INC
#define ISOSURFACE_INC
//
//  Forward declarations
//
//                   S i m o b j e c t    d e c l a r a t i o n
struct CIsoSurface : public tSimObj {
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

extern tObjLib isosurface_factory;

#endif  // ISOSURFACE_INC
