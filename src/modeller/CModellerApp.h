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
#include <QApplication>
#include <msgthread.h>
#include <simifc.h>
#include <coreifc.h>
#include <msg.h>
#include <QObject>
#include <ui_modeller.h>
#include <vector>
#include <variant.h>
#include <map>
#include <string>
#include <logthread.h>
#include <QSettings>
#include "IIncomingMessages.h"
#include "CModelStoreThread.h"
#include "IGUIInput.h"
#include <QMainWindow>
#include <QString>
#include "IFileMenu.h"
#include "IEditMenu.h"
#include "IViewMenu.h"
#include "ISettingsMenu.h"
#include "IHelpMenu.h"
#include "IModelInput.h"
#include "CGUI.h"
#include "CModelNode.h"
#include "eModelState.h"
#include <msgqueue.h>
#include "CModel.h"
#include "CSettings.h"
//
//  List of forwards needed in this module.
class CModelNode;
class CSettings;
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
