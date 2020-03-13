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
#include <msg.h>
#include <ui_modeller.h>
#include <msgqueue.h>
#include <logthread.h>
#include <QApplication>
#include "IIncomingMessages.h"
#include "CModelStoreThread.h"
#include <QObject>
#include "IGUIInput.h"
#include <QMainWindow>
#include "IFileMenu.h"
#include "IEditMenu.h"
#include "IViewMenu.h"
#include "ISettingsMenu.h"
#include "IHelpMenu.h"
#include "IModelInput.h"
#include "CGUI.h"
#include "CModel.h"
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
    CModel            mModel;
};

#endif  // CMODELLERAPP_INC
