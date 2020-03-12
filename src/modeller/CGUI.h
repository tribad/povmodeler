// *************************************************************************************************************
//
//  Modul-Name     : CGUI.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef CGUI_INC
#define CGUI_INC
#include <ui_modeller.h>
#include <QObject>
#include <QMainWindow>
#include "IFileMenu.h"
#include "IEditMenu.h"
//
//  This is the class
class CGUI : public QObject {
Q_OBJECT
public:
    virtual ~CGUI() = default;
    CGUI() ;
public:
    IEditMenu     mEditMenu;
private:
    Ui_MainWindow mUIMainWindow;
    QMainWindow   mMainWindow;
    IFileMenu     mFileMenu;
};

#endif  // CGUI_INC
