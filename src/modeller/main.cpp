// *************************************************************************************************************
//
//  Modul-Name     : main.cpp
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#include <msgthread.h>
#include <simifc.h>
#include <coreifc.h>
#include <logthread.h>
#include <ui_modeller.h>
#include "main.h"
#include <QApplication>
#include "CModelStoreThread.h"
#include <QMainWindow>
#include "CModellerApp.h"
// Optional
int main(int argc, char** argv) {
    int retval = 0;
// User-Defined-Code:AAAAAAFwukSfIpDfer4=
    CModellerApp application(argc, argv);

    application.exec();
// End-Of-UDC:AAAAAAFwukSfIpDfer4=
    return  (retval);
}

