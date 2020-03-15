// *************************************************************************************************************
//
//  Modul-Name     : CModelIdleState.cpp
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
#include "CModelIdleState.h"
// Optional
#include "../messages/tMsgStartImportReply.h"
#include "../messages/tMsgStartImportReq.h"
eModelState CModelIdleState::Process(CModelStateCtrl& aCtrl, tMsgStartImportReq* aMsg) {
    eModelState retval = eModelState::Idle;
// User-Defined-Code:AAAAAAFw3tFz8yvfUzo=
    //
    //  We do not delete the message as it would be send to the model store.
    retval = eModelState::Import;
// End-Of-UDC:AAAAAAFw3tFz8yvfUzo=
    return  (retval);
}

