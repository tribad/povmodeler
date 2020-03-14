// *************************************************************************************************************
//
//  Modul-Name     : CSettings.cpp
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
//
//  All needed headers in header file. This is needed for the moc tool.
#include "CSettings.h"
// Optional
CSettings& CSettings::instance(void) {
// User-Defined-Code:AAAAAAFw1BeQFVBNxNM=
    static CSettings retval;

    return retval;
// End-Of-UDC:AAAAAAFw1BeQFVBNxNM=
}

