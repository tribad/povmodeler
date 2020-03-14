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
    //
    //  File menu connections
    connect(mUIMainWindow.actionNew, SIGNAL(triggered()), &mFileMenu, SLOT(New()));
    connect(mUIMainWindow.actionOpen, SIGNAL(triggered()), &mFileMenu, SLOT(Load()));
    connect(mUIMainWindow.actionOpen_Recent, SIGNAL(triggered()), &mFileMenu, SLOT(LoadRecent()));
    connect(mUIMainWindow.actionSave, SIGNAL(triggered()), &mFileMenu, SLOT(Save()));
    connect(mUIMainWindow.actionClose, SIGNAL(triggered()), &mFileMenu, SLOT(Close()));
    //
    //  Edit menu connections
    connect(mUIMainWindow.actionCut, SIGNAL(triggered()), &mEditMenu, SLOT(Cut()));
    connect(mUIMainWindow.actionCopy, SIGNAL(triggered()), &mEditMenu, SLOT(Copy()));
    connect(mUIMainWindow.actionPaste, SIGNAL(triggered()), &mEditMenu, SLOT(Paste()));
    connect(mUIMainWindow.actionDelete, SIGNAL(triggered()), &mEditMenu, SLOT(Delete()));
    connect(mUIMainWindow.actionUndo, SIGNAL(triggered()), &mEditMenu, SLOT(Undo()));
    connect(mUIMainWindow.actionRedo, SIGNAL(triggered()), &mEditMenu, SLOT(Redo()));
    //
    //  File functions connections.
    connect(&mFileMenu, SIGNAL(Load(QString)), SLOT(Load(QString)));


// End-Of-UDC:AAAAAAFwzcKk4/mOpCI=
}

void CGUI::Load(QString aFileName) {
// User-Defined-Code:AAAAAAFw2C0TxW3A1eI=
// End-Of-UDC:AAAAAAFw2C0TxW3A1eI=
}

