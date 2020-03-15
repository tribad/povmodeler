// *************************************************************************************************************
//
//  Modul-Name     : CModelStateCtrl.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef CMODELSTATECTRL_INC
#define CMODELSTATECTRL_INC
//
//  List of forwards from forwards list.
class CModelNode;
//
//  This is the class
class CModelStateCtrl {
public:
    ~CModelStateCtrl() = default;
    CModelStateCtrl(IGUIInput& aGUIInput, CMsgQueue& aOutgoingMessage) ;
protected:
    IGUIInput&  mGUIInput;
    CMsgQueue&  mStoreOutput;
private:
    CModelNode  mRoot;
    CModelNode* mActual;
};

#endif  // CMODELSTATECTRL_INC
