// *************************************************************************************************************
//
//  Modul-Name     : CModellerApp.cpp
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
//
//  All needed headers in header file. This is needed for the moc tool.
#include "CModellerApp.h"
// Optional
CCoreIfc* __coreIfc;
CSimIfc* gStoreIfc;
CModellerApp::CModellerApp(int aArgc, char** aArgv) : QApplication(aArgc, aArgv) {
// User-Defined-Code:AAAAAAFwunztA5H0NRk=
    //
    //  Starting the logging thread and wait until its running. On fast multicore machines this
    //  is needed to allow the complete initialization of the thread before continue
    CLogThread::Instance.Create();
    while (!CLogThread::Instance.Running);

    __coreIfc = new CCoreIfc;
    gStoreIfc = siminit();

    mUIMainWindow.setupUi(&mMainWindow);

    mMainWindow.show();
// End-Of-UDC:AAAAAAFwunztA5H0NRk=
}

CModellerApp::~CModellerApp()  {
// User-Defined-Code:AAAAAAFwuoAt/JIQqI8=
// End-Of-UDC:AAAAAAFwuoAt/JIQqI8=
}

