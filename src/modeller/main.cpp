// *************************************************************************************************************
//
//  Modul-Name     : main.cpp
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#include <coreifc.h>
#include <logthread.h>
#include "main.h"
#include "CModellerApp.h"
// Optional
CCoreIfc __coreIfc;
int main(int argc, char** argv) {
    int retval = 0;
// User-Defined-Code:AAAAAAFwukSfIpDfer4=
    CModellerApp application(argc, argv);

    CLogThread::Instance.Create();
    while (!CLogThread::Instance.bRunning);
    application.exec();
// End-Of-UDC:AAAAAAFwukSfIpDfer4=
    return  (retval);
}

