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
eModelState CModelIdleState::Process(CModelStateCtrl& aCtrl, tMsg* aMsg) {
    eModelState retval = eModelState::Idle;
// User-Defined-Code:AAAAAAFw3fnHXRwi2r8=
// End-Of-UDC:AAAAAAFw3fnHXRwi2r8=
    return  (retval);
}

