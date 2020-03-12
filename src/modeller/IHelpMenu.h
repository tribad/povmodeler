// *************************************************************************************************************
//
//  Modul-Name     : IHelpMenu.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef IHELPMENU_INC
#define IHELPMENU_INC
#include <QObject>
//
//  This is the class
class IHelpMenu : public QObject {
Q_OBJECT
public:
    IHelpMenu() = default;
    virtual ~IHelpMenu() = default;
public slots:
    void About(void) ;
};

#endif  // IHELPMENU_INC
