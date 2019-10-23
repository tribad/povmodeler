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
//  Local includes.
#include "pmapp.h"

PMApp::PMApp(QObject *parent) : QObject(parent)
{
    mPMMainWindow.setupUi(&mMainWindow);
    //
    //  Create the interfaces.
    mIPMViewMenu = new IPMViewMenu((MPMViewMenu*)this);
    //
    //  Do the connections
    connect(mPMMainWindow.actionProperty, SIGNAL(triggered(bool)), mIPMViewMenu, SLOT(slotProperty(bool)));
    connect(mPMMainWindow.actionTop, SIGNAL(triggered(bool)), mIPMViewMenu, SLOT(slotTop(bool)));
    connect(mPMMainWindow.actionBottom, SIGNAL(triggered(bool)), mIPMViewMenu, SLOT(slotBottom(bool)));
    connect(mPMMainWindow.actionLeft, SIGNAL(triggered(bool)), mIPMViewMenu, SLOT(slotLeft(bool)));
    connect(mPMMainWindow.actionRight, SIGNAL(triggered(bool)), mIPMViewMenu, SLOT(slotRight(bool)));
    connect(mPMMainWindow.actionBack, SIGNAL(triggered(bool)), mIPMViewMenu, SLOT(slotBack(bool)));
    connect(mPMMainWindow.actionFront, SIGNAL(triggered(bool)), mIPMViewMenu, SLOT(slotFront(bool)));
    connect(mPMMainWindow.actionCamera, SIGNAL(triggered(bool)), mIPMViewMenu, SLOT(slotCamera(bool)));

    mMainWindow.show();
}


void PMApp::togglePropertyVisibility(bool changed) {
}

void PMApp::toggleGlView(GLView view, bool changed) {
}

void PMApp::setGlViewChecked(GLView view, bool checked) {
    if (view != GLView::Undefined) {

    }
}
