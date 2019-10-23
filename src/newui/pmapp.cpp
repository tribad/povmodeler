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
#include "pmxmlparser.h"

PMApp::PMApp(QObject *parent) : QObject(parent)
{
    mPMMainWindow.setupUi(&mMainWindow);
    //
    //  Create the interfaces.
    mSigPMViewMenu = new SigPMViewMenu((IPMViewMenu*)this);
    //
    //  Do the connections
    connect(mPMMainWindow.actionProperty, SIGNAL(triggered(bool)), mSigPMViewMenu, SLOT(slotProperty(bool)));
    connect(mPMMainWindow.actionTop,      SIGNAL(triggered(bool)), mSigPMViewMenu, SLOT(slotTop(bool)));
    connect(mPMMainWindow.actionBottom,   SIGNAL(triggered(bool)), mSigPMViewMenu, SLOT(slotBottom(bool)));
    connect(mPMMainWindow.actionLeft,     SIGNAL(triggered(bool)), mSigPMViewMenu, SLOT(slotLeft(bool)));
    connect(mPMMainWindow.actionRight,    SIGNAL(triggered(bool)), mSigPMViewMenu, SLOT(slotRight(bool)));
    connect(mPMMainWindow.actionBack,     SIGNAL(triggered(bool)), mSigPMViewMenu, SLOT(slotBack(bool)));
    connect(mPMMainWindow.actionFront,    SIGNAL(triggered(bool)), mSigPMViewMenu, SLOT(slotFront(bool)));
    connect(mPMMainWindow.actionCamera,   SIGNAL(triggered(bool)), mSigPMViewMenu, SLOT(slotCamera(bool)));

    mMainWindow.show();

    PMObjectList list;
    QIODevice* dev = new QFile( "test.kpm" );
    bool success = true;


    if( dev && dev->open( QIODevice::ReadOnly ) )
    {
        PMXMLParser parser( dev );
        parser.parse( &list, nullptr, nullptr );//step1

        PMObject* obj = list.first();
        if( obj )
        {
            if( obj->type() == "Scene" ) {
                mScene = obj;
            } else {
                success = false;
            }
        } else {
            success = false;
        }
    }

}


void PMApp::togglePropertyViewVisibility(bool changed) {
}

void PMApp::toggleGlViewVisibility(GLView view, bool changed) {
}

void PMApp::setGlViewChecked(GLView view, bool checked) {
    if (view != GLView::Undefined) {

    }
}
