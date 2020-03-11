// *************************************************************************************************************
//
//  Modul-Name     : CModelStoreThread.cpp
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#include <msgthread.h>
#include <simifc.h>
#include <coreifc.h>
#include "CModelStoreThread.h"
// Optional
CCoreIfc* __coreIfc;
CModelStoreThread::CModelStoreThread()  {
// User-Defined-Code:AAAAAAFwyK4jX/XQMGg=
    __coreIfc = new CCoreIfc;
    mStoreIfc = siminit();
// End-Of-UDC:AAAAAAFwyK4jX/XQMGg=
}

CModelStoreThread& CModelStoreThread::GetInstance(void) {
// User-Defined-Code:AAAAAAFwyKvB/vW7ltw=
    static CModelStoreThread instance;

    return instance;
// End-Of-UDC:AAAAAAFwyKvB/vW7ltw=
}

