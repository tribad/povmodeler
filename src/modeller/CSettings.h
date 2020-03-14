// *************************************************************************************************************
//
//  Modul-Name     : CSettings.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef CSETTINGS_INC
#define CSETTINGS_INC
//
//  This is a list of public macros
#define LAST_DIRECTORY_VISITED "lastdirvisited"
#define RECENTFILE_FILE_MAX    RECENTFILE_GROUP"/max"
#define RECENTFILE_GROUP       "recentfiles"
#define RECENTFILE_KEY_PREFIX  RECENTFILE_GROUP"/file"
#include <QSettings>
//
//  This is the class
class CSettings : public QSettings {
Q_OBJECT
public:
    CSettings() = default;
    virtual ~CSettings() = default;
    static CSettings& instance(void) ;
};

#endif  // CSETTINGS_INC
