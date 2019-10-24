// **************************************************************************
//
// Modul-Name        : pmapp.cpp
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 22.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
//
//
// Qt includes
#include <QIODevice>
#include <QFile>
//
//  Local includes.
#include "pmapp.h"

PMApp::PMApp(QObject *parent) : QObject(parent)
{
    //
    //  Using the qt-designer makes things a bit easier.
    mPMMainWindow.setupUi(&mMainWindow);
    //
    //  Create the interfaces.
    mSigPMFileMenu = new SigPMFileMenu((IPMFileMenu*)this);
    mSigPMViewMenu = new SigPMViewMenu((IPMViewMenu*)this);
    //
    //  Do the connections to the file menu.
    connect(mPMMainWindow.actionNew, SIGNAL(triggered()), mSigPMFileMenu, SLOT(slotNew()));
    connect(mPMMainWindow.actionOpen, SIGNAL(triggered()), mSigPMFileMenu, SLOT(slotLoad()));
    connect(mPMMainWindow.actionSave, SIGNAL(triggered()), mSigPMFileMenu, SLOT(slotSave()));
    connect(mPMMainWindow.actionQuit, SIGNAL(triggered()), mSigPMFileMenu, SLOT(slotExit()));
    //
    //  Do the connections to the view menu.
    connect(mPMMainWindow.actionProperty, SIGNAL(triggered(bool)), mSigPMViewMenu, SLOT(slotProperty(bool)));
    connect(mPMMainWindow.actionTop,      SIGNAL(triggered(bool)), mSigPMViewMenu, SLOT(slotTop(bool)));
    connect(mPMMainWindow.actionBottom,   SIGNAL(triggered(bool)), mSigPMViewMenu, SLOT(slotBottom(bool)));
    connect(mPMMainWindow.actionLeft,     SIGNAL(triggered(bool)), mSigPMViewMenu, SLOT(slotLeft(bool)));
    connect(mPMMainWindow.actionRight,    SIGNAL(triggered(bool)), mSigPMViewMenu, SLOT(slotRight(bool)));
    connect(mPMMainWindow.actionBack,     SIGNAL(triggered(bool)), mSigPMViewMenu, SLOT(slotBack(bool)));
    connect(mPMMainWindow.actionFront,    SIGNAL(triggered(bool)), mSigPMViewMenu, SLOT(slotFront(bool)));
    connect(mPMMainWindow.actionCamera,   SIGNAL(triggered(bool)), mSigPMViewMenu, SLOT(slotCamera(bool)));
    //
    //  Do some more initialization
    mActiveModel = nullptr;

    mMainWindow.show();
}
//
//  View Menu signal processing methods
void PMApp::togglePropertyViewVisibility(bool changed) {
}

void PMApp::toggleGlViewVisibility(GLView view, bool changed) {
}
//
//
void PMApp::setGlViewChecked(GLView view, bool checked) {
    if (view != GLView::Undefined) {

    }
}
//
// File menu signal processing methods.
void PMApp::doNew() {

}
void PMApp::doLoad() {

}
void PMApp::doSave() {

}
void PMApp::doClose() {

}
void PMApp::doExit() {
    for (auto model : mModels) {
        //
        //  Ask for saving for each modified model.
        if (model->isModified()) {

        }
    }
    mMainWindow.close();
}
//
//  Initialization
bool PMApp::Load(const QString& aPath) {
    bool retval = true;
    //
    //  We may throw an exception if the load fails and then return false.
    //  But for now we expect everything is ok.
    //
    //  Setting the active model to the new loaded one in a hurry.
    mModels.push_back(mActiveModel = new PMModel(aPath));
    return retval;
}

