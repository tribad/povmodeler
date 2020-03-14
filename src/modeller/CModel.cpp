// *************************************************************************************************************
//
//  Modul-Name     : CModel.cpp
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#include <msg.h>
#include <QXmlStreamReader>
#include <QFile>
#include <QString>
#include "IModelInput.h"
#include "IIncomingMessages.h"
#include "IGUIInput.h"
#include <msgqueue.h>
#include "CModel.h"
// Optional
CModel::CModel(IGUIInput& aGUIInput, CMsgQueue& aOutgoingMessage) : mGUIInput(aGUIInput),  mStoreOutput(aOutgoingMessage) {
// User-Defined-Code:AAAAAAFw04XnBkMJfPs=
// End-Of-UDC:AAAAAAFw04XnBkMJfPs=
}

void CModel::LoadKpovModelerFile(QString aFileName) {
// User-Defined-Code:AAAAAAFw2NpNF3fIStY=
    QXmlStreamReader xml;
    QFile            infile(aFileName);
    QXmlStreamReader::TokenType tt;

    infile.open(QIODevice::ReadOnly);

    xml.setDevice(&infile);

    while (!xml.atEnd()) {
        tt = xml.readNext();

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
// End-Of-UDC:AAAAAAFw2NpNF3fIStY=
}

