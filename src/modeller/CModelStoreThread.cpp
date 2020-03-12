// *************************************************************************************************************
//
//  Modul-Name     : CModelStoreThread.cpp
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#include <msgthread.h>
#include <msg.h>
#include <simifc.h>
#include <coreifc.h>
#include "CModelStoreThread.h"
// Optional
#include "IIncomingMessages.h"
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

void CModelStoreThread::Process(tMsg* aMsg) {
// User-Defined-Code:AAAAAAFwyQZvavvNUd8=
    if (aMsg != nullptr) {
        //
        //  This is the indicator to send the message to the model store.
        if (aMsg->dst.type == eCommTarget::Object) {
            if (mStoreIfc != nullptr) {
                tMsg* answer;
                answer = mStoreIfc->Process(aMsg);
                if (answer != nullptr) {
                    //
                    //  We are putting the answer into our queue to keep the
                    //  chronological order intact.
                    q.Put(answer);
                }
            }
        } else if (aMsg->dst.type == eCommTarget::Node) {
            mMsgToModeller->Process(aMsg);
        }
    }
// End-Of-UDC:AAAAAAFwyQZvavvNUd8=
}

