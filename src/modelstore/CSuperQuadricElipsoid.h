// *************************************************************************************************************
//
//  Modul-Name     : CSuperQuadricElipsoid.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef SUPERQUADRICELIPSOID_INC
#define SUPERQUADRICELIPSOID_INC
//
//  Forward declarations
//
//                   S i m o b j e c t    d e c l a r a t i o n
struct CSuperQuadricElipsoid : public tSimObj {
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

extern tObjLib superquadricelipsoid_factory;

#endif  // SUPERQUADRICELIPSOID_INC
