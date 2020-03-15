// *************************************************************************************************************
//
//  Modul-Name     : CModelBaseState.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef CMODELBASESTATE_INC
#define CMODELBASESTATE_INC
//
//  List of forwards from forwards list.
class CModelNode;
class tMsgStartImportReply;
//
//  This is the class
class CModelBaseState {
public:
    CModelBaseState() = default;
    virtual ~CModelBaseState() = default;
    virtual eModelState Process(CModelStateCtrl& aCtrl, tMsg* aMsg) ;
protected:
    virtual eModelState Process(CModelStateCtrl& aCtrl, tMsgStartImportReply* aMsg) ;
};

#endif  // CMODELBASESTATE_INC
