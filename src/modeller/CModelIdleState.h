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
//  List of forwards from forwards list.
class CModelNode;
class tMsgStartImportReply;
//
//  This is the class
class CModelIdleState : public CModelBaseState {
public:
    CModelIdleState() = default;
    virtual ~CModelIdleState() = default;
protected:
    virtual eModelState Process(CModelStateCtrl& aCtrl, tMsgStartImportReply* aMsg) ;
};

#endif  // CMODELIDLESTATE_INC
