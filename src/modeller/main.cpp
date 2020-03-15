// *************************************************************************************************************
//
//  Modul-Name     : main.cpp
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
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
#include "main.h"
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
#include "CModellerApp.h"
// Optional
#include "../messages/tMsgStartImportReply.h"
#include "CModelBaseState.h"
#include <QApplication>
#include <QObject>
#include <QMainWindow>
#include <QObject>
#include <QString>
#include <QObject>
#include <QObject>
#include <QObject>
#include <QObject>
#include <QString>
#include <QString>
#include ".././CMsgQueue.h"
#include <QString>
    int retval = 0;
// User-Defined-Code:AAAAAAFwukSfIpDfer4=
    CModellerApp application(argc, argv);

    retval = application.exec();
// End-Of-UDC:AAAAAAFwukSfIpDfer4=
    return  (retval);
}

