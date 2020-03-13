// *************************************************************************************************************
//
//  Modul-Name     : CGUI.cpp
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
//
//  All needed headers in header file. This is needed for the moc tool.
#include "CGUI.h"
// Optional
CGUI::CGUI(IModelInput& aModelInput) : CGUI::QObject(nullptr) {
// User-Defined-Code:AAAAAAFwzcKk4/mOpCI=
    //
    //  Create the main window
    mUIMainWindow.setupUi(&mMainWindow);

    mMainWindow.show();

    CGUI::connect(mUIMainWindow.actionNew, SIGNAL(triggered()), &mFileMenu, SLOT(New()));
    connect(mUIMainWindow.actionOpen, SIGNAL(triggered()), &mFileMenu, SLOT(Load()));
    connect(mUIMainWindow.actionOpen_Recent, SIGNAL(triggered()), &mFileMenu, SLOT(LoadRecent()));
    connect(mUIMainWindow.actionSave, SIGNAL(triggered()), &mFileMenu, SLOT(Save()));
    connect(mUIMainWindow.actionClose, SIGNAL(triggered()), &mFileMenu, SLOT(Close()));

    connect(mUIMainWindow.actionCut, SIGNAL(triggered()), &mEditMenu, SLOT(Cut()));
    connect(mUIMainWindow.actionCopy, SIGNAL(triggered()), &mEditMenu, SLOT(Copy()));
    connect(mUIMainWindow.actionPaste, SIGNAL(triggered()), &mEditMenu, SLOT(Paste()));
    connect(mUIMainWindow.actionDelete, SIGNAL(triggered()), &mEditMenu, SLOT(Delete()));
    connect(mUIMainWindow.actionUndo, SIGNAL(triggered()), &mEditMenu, SLOT(Undo()));
    connect(mUIMainWindow.actionRedo, SIGNAL(triggered()), &mEditMenu, SLOT(Redo()));

// End-Of-UDC:AAAAAAFwzcKk4/mOpCI=
}

