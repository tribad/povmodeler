// *************************************************************************************************************
//
//  Modul-Name     : CModelStateCtrl.cpp
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#include <vector>
#include <variant.h>
#include <map>
#include <string>
#include <msgqueue.h>
#include "IGUIInput.h"
#include "CModelNode.h"
#include "CModelStateCtrl.h"
// Optional
CModelStateCtrl::CModelStateCtrl(IGUIInput& aGUIInput, CMsgQueue& aOutgoingMessage) : mGUIInput(aGUIInput),  mStoreOutput(aOutgoingMessage) {
// User-Defined-Code:AAAAAAFw3fC53xDzng4=
    mActual = &mRoot;
// End-Of-UDC:AAAAAAFw3fC53xDzng4=
}

