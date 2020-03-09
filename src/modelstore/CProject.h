// *************************************************************************************************************
//
//  Modul-Name     : CProject.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef PROJECT_INC
#define PROJECT_INC
//
//  Forward declarations
//
//                   S i m o b j e c t    d e c l a r a t i o n
struct CProject : public tSimObj, public CObjectBase {
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
    CSimAttribute Name;
};

extern tObjLib project_factory;

#endif  // PROJECT_INC
