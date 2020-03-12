// *************************************************************************************************************
//
//  Modul-Name     : main.cpp
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#include <msgthread.h>
#include <msg.h>
#include <simifc.h>
#include <coreifc.h>
#include <ui_modeller.h>
#include <logthread.h>
#include "main.h"
#include <QApplication>
#include "IIncomingMessages.h"
#include "CModelStoreThread.h"
#include <QObject>
#include <QMainWindow>
#include "IFileMenu.h"
#include "IEditMenu.h"
#include "IViewMenu.h"
#include "ISettingsMenu.h"
#include "IHelpMenu.h"
#include "CGUI.h"
#include "CModellerApp.h"
// Optional
int main(int argc, char** argv) {
    int retval = 0;
// User-Defined-Code:AAAAAAFwukSfIpDfer4=
    CModellerApp application(argc, argv);

    retval = application.exec();
// End-Of-UDC:AAAAAAFwukSfIpDfer4=
    return  (retval);
}

