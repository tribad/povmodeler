// **************************************************************************
//
// Modul-Name        :
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     :
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************

#include "pmsettings.h"

PMSettings::PMSettings() : QSettings()
{

}
//
//  This is a singleton pattern. But it has the advantage that
//  the QSettings constructor gets called on the first usage, that should
//  be after all initialization of QCoreApplication has been done.
PMSettings& PMSettings::settings() {
    static PMSettings mSettings;

    return mSettings;
}
