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
class tMsgStartImportReq;
//
//                   S i m o b j e c t    d e c l a r a t i o n
struct CProject : public tSimObj {
    /*
     *  These are the message and signal processing functions.
     */
public:
    tMsg* process(tMsgStartImportReq* msg) ;
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
    CSimAttrArray                  Scenes;
    CSimAttrArray                  contained;
};

extern tObjLib project_factory;

#endif  // PROJECT_INC
