// *************************************************************************************************************
//
//  Modul-Name     : IFileMenu.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef IFILEMENU_INC
#define IFILEMENU_INC
#include <QObject>
//
//  This is the class
class IFileMenu : public QObject {
Q_OBJECT
public:
    IFileMenu() = default;
    virtual ~IFileMenu() = default;
public slots:
    void New(void) ;
    void Load(void) ;
    void LoadRecent(void) ;
    void Save(void) ;
    void Close(void) ;
};

#endif  // IFILEMENU_INC
