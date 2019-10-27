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

PMSettings PMSettings::mSettings;

PMSettings::PMSettings() : QSettings("Simulated-Universe", "povmodeler")
{

}
