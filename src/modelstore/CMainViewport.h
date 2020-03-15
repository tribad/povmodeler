// *************************************************************************************************************
//
//  Modul-Name     : CMainViewport.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef MAINVIEWPORT_INC
#define MAINVIEWPORT_INC
//
//  Forward declarations
class tMsgStartImportReq;
class tMsgAddElementReq;
//
//                   S i m o b j e c t    d e c l a r a t i o n
struct CMainViewport : public tSimObj {
    /*
     *  These are the message and signal processing functions.
     */
public:
    tMsg* process(tMsgStartImportReq* msg) ;
    tMsg* process(tMsgAddElementReq* msg) ;
    tMsg* DefaultMsgHandler(tMsg* aMsg);
    bool  DefaultSigHandler(tSig* aSignal);
    /*
     *  Here are the attributes of the object defined.
     */
public:
};

extern tObjLib mainviewport_factory;

#endif  // MAINVIEWPORT_INC
