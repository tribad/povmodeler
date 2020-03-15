// *************************************************************************************************************
//
//  Modul-Name     : CModelIdleState.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef CMODELIDLESTATE_INC
#define CMODELIDLESTATE_INC
//
//  List of forwards needed in this module.
class CModelNode;
//
//  This is the class
class CModelIdleState : public CModelBaseState {
public:
    CModelIdleState() = default;
    virtual ~CModelIdleState() = default;
    virtual eModelState Process(CModelStateCtrl& aCtrl, tMsg* aMsg) ;
};

#endif  // CMODELIDLESTATE_INC
