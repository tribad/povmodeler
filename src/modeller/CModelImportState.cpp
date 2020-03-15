// *************************************************************************************************************
//
//  Modul-Name     : CModelImportState.cpp
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
#include "CModelImportState.h"
// Optional
#include "../messages/tMsgStartImportReply.h"
