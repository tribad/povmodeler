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
#include <msg.h>
#include <simifc.h>
#include <coreifc.h>
#include <ui_modeller.h>
#include <logthread.h>
#include <QApplication>
#include "CModelStoreThread.h"
#include <QObject>
#include <QMainWindow>
#include "IFileMenu.h"
#include "IEditMenu.h"
#include "CGUI.h"
//
//  List of forwards needed in this module.
class IIncomingMessages;
//
//  This is the class
class CModellerApp : public QApplication {
Q_OBJECT
public:
    CModellerApp(int& aArgc, char** aArgv) ;
    virtual ~CModellerApp() ;
public:
    CModelStoreThread mStoreThread;
private:
    CGUI              mGUI;
};

#endif  // CMODELLERAPP_INC
