// *************************************************************************************************************
//
//  Modul-Name     : CScene.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef SCENE_INC
#define SCENE_INC
//
//  Forward declarations
class tMsgStartImportReq;
class tMsgAddElementReq;
//
//                   S i m o b j e c t    d e c l a r a t i o n
struct CScene : public tSimObj {
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
    CSimAttribute                  FileName;
    CSimAttribute                  Name;
    std::map< uint64_t, tVariant > ObjectsBefore;
    std::map< uint64_t, tVariant > ObjectsAfter;
    CSimAttrArray                  contained;
};

extern tObjLib scene_factory;

#endif  // SCENE_INC
