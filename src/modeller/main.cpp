// *************************************************************************************************************
//
//  Modul-Name     : main.cpp
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#include <coreifc.h>
#include <simifc.h>
#include <logthread.h>
#include "main.h"
#include <QApplication>
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

