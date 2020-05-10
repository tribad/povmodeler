// *************************************************************************************************************
//
//  Modul-Name     : CCamera.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef CAMERA_INC
#define CAMERA_INC
//
//  Forward declarations
class tMsgAddElementReq;
//
//                   S i m o b j e c t    d e c l a r a t i o n
struct CCamera : public tSimObj {
    /*
     *  These are the message and signal processing functions.
     */
public:
    tMsg* process(tMsgAddElementReq* msg) ;
    tMsg* DefaultMsgHandler(tMsg* aMsg);
    bool  DefaultSigHandler(tSig* aSignal);
    /*
     *  Here are the attributes of the object defined.
     */
public:
    CSimAttribute                  Name;
    std::map< uint64_t, tVariant > ObjectsBefore;
    std::map< uint64_t, tVariant > ObjectsAfter;
    CSimAttrArray                  contained;
};

extern tObjLib camera_factory;

#endif  // CAMERA_INC
