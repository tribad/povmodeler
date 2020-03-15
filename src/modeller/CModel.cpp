// *************************************************************************************************************
//
//  Modul-Name     : CModel.cpp
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#include <msg.h>
#include <vector>
#include <variant.h>
#include <map>
#include <string>
#include <QXmlStreamReader>
#include <QFile>
#include "IIncomingMessages.h"
#include <QString>
#include "IModelInput.h"
#include "IGUIInput.h"
#include "CModelNode.h"
#include "eModelState.h"
#include <msgqueue.h>
#include "CModel.h"
// Optional
#include "tMsgStartImportReply.h"
#include "tMsgAddElementReply.h"
#include "tMsgStartImportReq.h"
#include "tMsgAddElementReq.h"
CModel::CModel(IGUIInput& aGUIInput, CMsgQueue& aOutgoingMessage) : mGUIInput(aGUIInput),  mStoreOutput(aOutgoingMessage) {
// User-Defined-Code:AAAAAAFw04XnBkMJfPs=
    mActual = &mRoot;
    mState  = eModelState::Idle;
// End-Of-UDC:AAAAAAFw04XnBkMJfPs=
}

void CModel::LoadKpovModelerFile(QString aFileName) {
// User-Defined-Code:AAAAAAFw2NpNF3fIStY=
    QXmlStreamReader            xml;
    QFile                       infile(aFileName);
    QXmlStreamReader::TokenType tt;
    //
    //  Do the open
    infile.open(QIODevice::ReadOnly);
    if (infile.isOpen()) {
        tMsg* startreq = new tMsgStartImportReq ;

        startreq->dst  = {0, nullptr};
        mStoreOutput.Put(startreq);
        //
        // Only working on an open file.
        xml.setDevice(&infile);
        //
        //  Run as long as there is no error.
        while (!xml.atEnd()) {
            tt = xml.readNext();
            //
            //  Check for errors before do any further processing.
            if (!xml.hasError()) {
                std::cerr << "------\n";
                std::cerr << tt << std::endl;

                for (auto a : xml.attributes()) {
                    std::cerr << a.name().toString().toStdString().c_str() << "::" << a.value().toString().toStdString().c_str() << std::endl;
                }
            } else {
                std::cerr << xml.errorString().toStdString().c_str() << std::endl;
            }
        }
    }
// End-Of-UDC:AAAAAAFw2NpNF3fIStY=
}

void CModel::Process(tMsg* aMsg) {
// User-Defined-Code:AAAAAAFw3agVRf3SzQg=
// End-Of-UDC:AAAAAAFw3agVRf3SzQg=
}

