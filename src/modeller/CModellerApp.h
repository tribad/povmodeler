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
#include <msg.h>
#include <simifc.h>
#include <coreifc.h>
#include <QObject>
#include <ui_modeller.h>
#include <vector>
#include <variant.h>
#include <map>
#include <string>
#include <msgqueue.h>
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
#include "CModelStateCtrl.h"
#include "eModelState.h"
#include "CModel.h"
#include "CSettings.h"
//
//  List of forwards from forwards list.
class CModelNode;
class CModelBaseState;
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
//
//  These are the operations defined with package scope.
int main(int argc, char** argv) ;

#endif  // CMODELLERAPP_INC
