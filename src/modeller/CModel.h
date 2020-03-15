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
class CModel : public IIncomingMessages, public IModelInput {
public:
    virtual ~CModel() = default;
    CModel(IGUIInput& aGUIInput, CMsgQueue& aOutgoingMessage) ;
    virtual void LoadKpovModelerFile(QString aFileName) ;
    virtual void Process(tMsg* aMsg) ;
public:
    IGUIInput&  mGUIInput;
    eModelState mState;
    CMsgQueue&  mStoreOutput;
private:
    CModelNode  mRoot;
    CModelNode* mActual;
};

#endif  // CMODEL_INC
