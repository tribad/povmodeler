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
//  List of forwards from forwards list.
class CModelNode;
class tMsgStartImportReply;
//
//  This is the class
class CModelLoadingState : public CModelBaseState {
public:
    CModelLoadingState() = default;
    virtual ~CModelLoadingState() = default;
};

#endif  // CMODELLOADINGSTATE_INC
