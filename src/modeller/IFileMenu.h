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
#include <QDir>
#include <QFileDialog>
#include <QObject>
#include <QString>
#include <QSettings>
#include "CSettings.h"
//
//  List of forwards needed in this module.
class CSettings;
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
signals:
    void Load(QString aFileName) ;
};

#endif  // IFILEMENU_INC
