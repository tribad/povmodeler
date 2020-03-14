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
#include <QSettings>
#include "CSettings.h"
CModellerApp::CModellerApp(int& aArgc, char** aArgv) : QApplication(aArgc, aArgv), mStoreThread(mModel), mGUI(mModel), mModel(mGUI, mStoreThread.q) {
// User-Defined-Code:AAAAAAFwunztA5H0NRk=
    QCoreApplication::setOrganizationName( "povmodeler" );
    QCoreApplication::setApplicationName( "povmodeler" );
    //
    //  Starting the logging thread and wait until its running. On fast multicore machines this
    //  is needed to allow the complete initialization of the thread before continue
    CLogThread::Instance.Create();
    while (!CLogThread::Instance.Running) ;
    //
    //  As of the singleton behaviour the constructor of CModelStoreThread gets called yet
    //  We wait as with the logthread until it is up and running.
    mStoreThread.Create();
    while (!mStoreThread.Running) ;
// End-Of-UDC:AAAAAAFwunztA5H0NRk=
}

CModellerApp::~CModellerApp()  {
// User-Defined-Code:AAAAAAFwuoAt/JIQqI8=
// End-Of-UDC:AAAAAAFwuoAt/JIQqI8=
}

