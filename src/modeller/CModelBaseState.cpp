// *************************************************************************************************************
//
//  Modul-Name     : CModelBaseState.cpp
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
// Optional
#include "../messages/tMsgStartImportReply.h"
eModelState CModelBaseState::Process(CModelStateCtrl& aCtrl, tMsgStartImportReply* aMsg) {
    eModelState retval = eModelState::Idle;
// User-Defined-Code:AAAAAAFw3kIa4yYmPHs=
// End-Of-UDC:AAAAAAFw3kIa4yYmPHs=
    return  (retval);
}

eModelState CModelBaseState::Process(CModelStateCtrl& aCtrl, tMsg* aMsg) {
    eModelState retval = eModelState::Idle;
// User-Defined-Code:AAAAAAFw3fg5JRrGZv4=
    switch (aMsg->id) {
    case IDM_STARTIMPORTREPLY:
        retval = Process(aCtrl, (tMsgStartImportReply*)aMsg);
        break;
    default:
        break;
    }

// End-Of-UDC:AAAAAAFw3fg5JRrGZv4=
    return  (retval);
}

