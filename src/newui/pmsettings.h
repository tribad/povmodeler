// **************************************************************************
//
// Modul-Name        :
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     :
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************

#ifndef PMSETTINGS_H
#define PMSETTINGS_H

#include <QSettings>

class PMSettings : public QSettings
{
public:
    PMSettings();
    static PMSettings mSettings;
};

#endif // PMSETTINGS_H
