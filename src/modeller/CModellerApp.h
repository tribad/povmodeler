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
#include <coreifc.h>
#include <simifc.h>
#include <logthread.h>
#include <ui_modeller.h>
#include <QApplication>
#include <QMainWindow>
//
//  This is the class
class CModellerApp : public QApplication {
Q_OBJECT
public:
    CModellerApp(int aArgc, char** aArgv) ;
    virtual ~CModellerApp() ;
private:
    QMainWindow   mMainWindow;
    Ui_MainWindow mUIMainWindow;
};
extern CCoreIfc* __coreIfc;
extern CSimIfc*  gStoreIfc;

#endif  // CMODELLERAPP_INC
