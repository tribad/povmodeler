// **************************************************************************
//
// Modul-Name        : pmsettings.h
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 27.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************

#ifndef PMSETTINGS_H
#define PMSETTINGS_H

#include <QSettings>
//
//  Some keys, groups and other to be used within the settings.
//
//  Recentfiles List.
#define RECENTFILE_GROUP      "recentfiles"
#define RECENTFILE_FILE_MAX   RECENTFILE_GROUP"/max"
#define RECENTFILE_KEY_PREFIX RECENTFILE_GROUP"/file"

class PMSettings : public QSettings
{
public:
    PMSettings();
    static PMSettings& instance();
private:
};

#endif // PMSETTINGS_H
