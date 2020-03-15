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
#include <msgqueue.h>
#include <QXmlStreamReader>
#include <QFile>
#include "IIncomingMessages.h"
#include <QString>
#include "IModelInput.h"
#include "IGUIInput.h"
#include "CModelNode.h"
#include "CModelStateCtrl.h"
#include "eModelState.h"
#include "CModel.h"
#include "CModelBaseState.h"
#include "CModelIdleState.h"
#include "CModelLoadingState.h"
#include <QXmlStreamReader>
#include <QFile>
#include "CModelImportState.h"
// Optional
#include "../messages/tMsgStartImportReply.h"
#include "../messages/tMsgStartImportReq.h"
#include <QXmlStreamReader>
#include <QFile>
#include "tMsgAddElementReply.h"
#include "tMsgAddElementReq.h"
void CModel::ProcessIdle(tMsg* aMsg) {
// User-Defined-Code:AAAAAAFw3eVTGgyJsF8=
    //
    // We are not deleting the message. Its done outside.
    switch (aMsg->id) {
    case IDM_STARTIMPORTREPLY:
        break;
    default:
        break;
    }
// End-Of-UDC:AAAAAAFw3eVTGgyJsF8=
}

CModel::CModel(IGUIInput& aGUIInput, CMsgQueue& aOutgoingMessage) : CModelStateCtrl(aGUIInput, aOutgoingMessage) {
// User-Defined-Code:AAAAAAFw04XnBkMJfPs=
    //
    //  Initialization of the statemachine
    mState  = eModelState::Idle;
    mStateList = {new CModelIdleState, new CModelLoadingState, new CModelImportState};
// End-Of-UDC:AAAAAAFw04XnBkMJfPs=
}

void CModel::LoadKpovModelerFile(QString aFileName) {
// User-Defined-Code:AAAAAAFw2NpNF3fIStY=
    tMsgStartImportReq* startreq = new tMsgStartImportReq ;

    startreq->dst  = {0, nullptr};
    startreq->FileName = aFileName.toStdString();
    //
    //  We do send the message first into the actual state.
    //  This can be achieved by calling our own process method.
    //  This should switch into the right state for to receive the reply.
    Process(startreq);
    //
    //  Now we should be in the right state and can send the message to the model store.
    if (mState == eModelState::Import) {
        mStoreOutput.Put(startreq);
    } else {

    }
#if 0
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
#endif

// End-Of-UDC:AAAAAAFw2NpNF3fIStY=
}

void CModel::Process(tMsg* aMsg) {
// User-Defined-Code:AAAAAAFw3agVRf3SzQg=
    if (mState != eModelState::EmergencySafe) {
        mState = mStateList[(unsigned)mState]->Process(*this, aMsg);
    }
// End-Of-UDC:AAAAAAFw3agVRf3SzQg=
}

