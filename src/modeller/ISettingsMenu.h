// *************************************************************************************************************
//
//  Modul-Name     : ISettingsMenu.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef ISETTINGSMENU_INC
#define ISETTINGSMENU_INC
#include <QObject>
//
//  This is the class
class ISettingsMenu : public QObject {
Q_OBJECT
public:
    ISettingsMenu() = default;
    virtual ~ISettingsMenu() = default;
public slots:
    void Options(void) ;
};

#endif  // ISETTINGSMENU_INC
