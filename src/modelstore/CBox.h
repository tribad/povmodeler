// *************************************************************************************************************
//
//  Modul-Name     : CBox.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef BOX_INC
#define BOX_INC
//
//  Forward declarations
//
//                   S i m o b j e c t    d e c l a r a t i o n
struct CBox : public tSimObj {
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

extern tObjLib box_factory;

#endif  // BOX_INC
