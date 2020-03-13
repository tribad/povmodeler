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
#include "IGUIInput.h"
#include <QMainWindow>
#include "IFileMenu.h"
#include "IEditMenu.h"
#include "IViewMenu.h"
#include "ISettingsMenu.h"
#include "IHelpMenu.h"
#include "IModelInput.h"
//
//  This is the class
class CGUI : public QObject, public IGUIInput {
Q_OBJECT
public:
    virtual ~CGUI() = default;
    CGUI(IModelInput& aModelInput) ;
private:
    Ui_MainWindow mUIMainWindow;
    QMainWindow   mMainWindow;
    IFileMenu     mFileMenu;
    IEditMenu     mEditMenu;
    IViewMenu     mViewMenu;
    ISettingsMenu mSettingsMenu;
    IHelpMenu     mHelpMenu;
};

#endif  // CGUI_INC
