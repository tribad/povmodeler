// *************************************************************************************************************
//
//  Modul-Name     : CModellerApp.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef CMODELLERAPP_INC
#define CMODELLERAPP_INC
#include <msgthread.h>
#include <simifc.h>
#include <coreifc.h>
#include <logthread.h>
#include <ui_modeller.h>
#include <QApplication>
#include "CModelStoreThread.h"
#include <QMainWindow>
//
//  This is the class
class CModellerApp : public QApplication {
Q_OBJECT
public:
    CModellerApp(int aArgc, char** aArgv) ;
    virtual ~CModellerApp() ;
public:
    CModelStoreThread mStoreThread;
private:
    Ui_MainWindow     mUIMainWindow;
    QMainWindow       mMainWindow;
};

#endif  // CMODELLERAPP_INC
