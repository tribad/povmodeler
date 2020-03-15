// *************************************************************************************************************
//
//  Modul-Name     : CModel.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef CMODEL_INC
#define CMODEL_INC
//
//  List of forwards needed in this module.
class CModelNode;
class tMsgStartImportReply;
class tMsgAddElementReply;
//
//  This is the class
class CModel : public IIncomingMessages, public IModelInput, public CModelStateCtrl {
public:
    virtual ~CModel() = default;
    CModel(IGUIInput& aGUIInput, CMsgQueue& aOutgoingMessage) ;
    virtual void LoadKpovModelerFile(QString aFileName) ;
    virtual void Process(tMsg* aMsg) ;
private:
    void ProcessIdle(tMsg* aMsg) ;
public:
    eModelState mState;
};

#endif  // CMODEL_INC
