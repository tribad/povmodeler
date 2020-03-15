// *************************************************************************************************************
//
//  Modul-Name     : CModelLoadingState.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef CMODELLOADINGSTATE_INC
#define CMODELLOADINGSTATE_INC
//
//  List of forwards needed in this module.
class CModelNode;
//
//  This is the class
class CModelLoadingState : public CModelBaseState {
public:
    CModelLoadingState() = default;
    virtual ~CModelLoadingState() = default;
    virtual eModelState Process(CModelStateCtrl& aCtrl, tMsg* aMsg) ;
};

#endif  // CMODELLOADINGSTATE_INC
