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
eModelState CModelIdleState::Process(CModelStateCtrl& aCtrl, tMsgStartImportReply* aMsg) {
    eModelState retval = eModelState::Idle;
// User-Defined-Code:AAAAAAFw3kO/hyY5nhY=
// End-Of-UDC:AAAAAAFw3kO/hyY5nhY=
    return  (retval);
}

