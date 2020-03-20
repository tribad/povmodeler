// *************************************************************************************************************
//
//  Modul-Name     : CModelImportKpmState.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef CMODELIMPORTKPMSTATE_INC
#define CMODELIMPORTKPMSTATE_INC
//
//  List of forwards from forwards list.
class CModelNode;
class tMsgStartImportReply;
class tMsgStartImportReq;
//
//  This is the class
class CModelImportKpmState : public CModelBaseState {
public:
    CModelImportKpmState() = default;
    virtual ~CModelImportKpmState() = default;
protected:
    virtual eModelState Process(CModelStateCtrl& aCtrl, tMsgStartImportReply* aMsg) ;
public:
    QXmlStreamReader xmlDocument;
    QFile            mInFile;
};

#endif  // CMODELIMPORTKPMSTATE_INC
