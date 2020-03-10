// *************************************************************************************************************
//
//  Modul-Name     : CLightSource.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef LIGHTSOURCE_INC
#define LIGHTSOURCE_INC
//
//  Forward declarations
//
//                   S i m o b j e c t    d e c l a r a t i o n
struct CLightSource : public tSimObj {
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
    CSimAttribute                  Name;
    std::map< uint64_t, tVariant > ObjectsBefore;
    std::map< uint64_t, tVariant > ObjectsAfter;
    CSimAttrArray                  contained;
};

extern tObjLib lightsource_factory;

#endif  // LIGHTSOURCE_INC
