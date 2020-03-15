// *************************************************************************************************************
//
//  Modul-Name     : CModelImportState.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef CMODELIMPORTSTATE_INC
#define CMODELIMPORTSTATE_INC
//
//  List of forwards needed in this module.
class CModelNode;
//
//  This is the class
class CModelImportState : public CModelBaseState {
public:
    CModelImportState() = default;
    virtual ~CModelImportState() = default;
    virtual eModelState Process(CModelStateCtrl& aCtrl, tMsg* aMsg) ;
};

#endif  // CMODELIMPORTSTATE_INC
