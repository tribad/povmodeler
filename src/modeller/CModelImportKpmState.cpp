// *************************************************************************************************************
//
//  Modul-Name     : CModelImportKpmState.cpp
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#include <vector>
#include <variant.h>
#include <map>
#include <string>
#include <msgqueue.h>
#include <msg.h>
#include "IGUIInput.h"
#include "CModelNode.h"
#include "CModelStateCtrl.h"
#include "eModelState.h"
#include "CModelBaseState.h"
#include <QXmlStreamReader>
#include <QFile>
#include "CModelImportKpmState.h"
// Optional
#include "../messages/tMsgStartImportReply.h"
#include "../messages/tMsgStartImportReq.h"
eModelState CModelImportKpmState::Process(CModelStateCtrl& aCtrl, tMsgStartImportReply* aMsg) {
    eModelState retval = eModelState::Idle;
// User-Defined-Code:AAAAAAFw3kO/hyY5nhY=
    QXmlStreamReader::TokenType token_type;

    mInFile.setFileName(QString(aMsg->FileName.c_str()));
    //
    //  Do the open
    mInFile.open(QIODevice::ReadOnly);
    if (mInFile.isOpen()) {
        //
        // Only working on an open file.
        xmlDocument.setDevice(&mInFile);
        //
        //  Run as long as there is no error.
        while (!xmlDocument.atEnd()) {
            token_type = xmlDocument.readNext();

            if (!xmlDocument.hasError()) {
                for (auto a : xmlDocument.attributes()) {
                    std::cerr << a.name().toString().toStdString().c_str() << "::" << a.value().toString().toStdString().c_str() << std::endl;
                }
            }
        }
    }
    delete aMsg;
// End-Of-UDC:AAAAAAFw3kO/hyY5nhY=
    return  (retval);
}

