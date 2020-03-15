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
//  List of forwards from forwards list.
class CModelNode;
class tMsgStartImportReply;
class tMsgStartImportReq;
//
//  This is the class
class CModelImportState : public CModelBaseState {
public:
    CModelImportState() = default;
    virtual ~CModelImportState() = default;
protected:
    virtual eModelState Process(CModelStateCtrl& aCtrl, tMsgStartImportReply* aMsg) ;
public:
    QXmlStreamReader xmlDocument;
    QFile            mInFile;
};

#endif  // CMODELIMPORTSTATE_INC
