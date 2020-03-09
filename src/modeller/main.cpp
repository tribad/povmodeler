// *************************************************************************************************************
//
//  Modul-Name     : main.cpp
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#include <simifc.h>
#include <coreifc.h>
#include <logthread.h>
#include <appcore/0.1.4/tMsgStartCycleReq.h>
#include "main.h"
#include "CModellerApp.h"
// Optional
CCoreIfc* __coreIfc;
int main(int argc, char** argv) {
    int retval = 0;
// User-Defined-Code:AAAAAAFwukSfIpDfer4=
    CModellerApp application(argc, argv);
    //
    //  Starting the logging thread and wait until its running. On fast multicore machines this
    //  is needed to allow the complete initialization of the thread before continue
    CLogThread::Instance.Create();
    while (!CLogThread::Instance.Running);

    __coreIfc = new CCoreIfc;
    CSimIfc* mysim = siminit();
    tMsg* startmsg = new tMsgStartCycleReq();

    startmsg->dst = tCommTarget(0, nullptr);
    mysim->Process(startmsg);
    application.exec();
// End-Of-UDC:AAAAAAFwukSfIpDfer4=
    return  (retval);
}

