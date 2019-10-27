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
#include "pmsettings.h"
#include "widgets/pmfactory.h"

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
    //  Do connections to the tree widget
    connect(mPMMainWindow.dockWidgetContents, SIGNAL(clicked(const QModelIndex&)), this, SLOT(selectedInTree(const QModelIndex&)) );
    //
    //  Do some more initialization
    //  Gui stuff first
    mPMMainWindow.treeDockWidget->setWindowTitle("Browser");
    //
    // others.
    mActiveModel = nullptr;
    mRecentFiles.Load();
    mMainWindow.show();
}
//
//  Direct Slots
void PMApp::selectedInTree(const QModelIndex &index) {
    //
    // Security check of active model.
    if (mActiveModel != nullptr) {
        QString itemtype = mActiveModel->GetItemType(index);

        if (!itemtype.isEmpty()) {
            widget::PMEditBase* propertyWidget = widget::PMFactory::Create(itemtype);

            if (propertyWidget != nullptr) {
                propertyWidget->setParent(mPMMainWindow.propertyDockWidget);
                mPMMainWindow.propertyDockWidget->setWidget(propertyWidget);
                propertyWidget->SetupData(static_cast<PMObject*>(index.internalPointer()));
                propertyWidget->show();
            } else {
                mPMMainWindow.propertyDockWidget->setWidget(nullptr);
            }
        }
    }

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
    mModels.insert(mActiveModel = new PMModel());
    //
    //  Do fill the model with some default elements.
    //  We could do this in the constructor, but this way it is visible that
    //  other ways of creating an initial model are possible.
    //
    //  We are not checking the pointer here as the constructor throws an
    //  out-of-memory exception anyway if no memory is available for the new object.
    mActiveModel->Load("__default.kpm");
    //
    //  Attach the model to the tree view
    mPMMainWindow.dockWidgetContents->setModel(mActiveModel);
}
void PMApp::doLoad() {

}
void PMApp::doSave() {

}
void PMApp::doClose() {
    //
    //  Check if any model is available.
    if (mActiveModel != nullptr) {
        //
        //  Ask for saving for each modified model.
        if (mActiveModel->isModified()) {

        }
        //
        //  Removing the active model from the list of models.
        mModels.erase(mActiveModel);
        //
        //  The destructor shall do the cleanup.
        delete mActiveModel;
        //
        //  Now take the first in the set. If we have none left
        //  clear the mActiveModel pointer
        if (mModels.begin() != mModels.end()) {
            mActiveModel = *mModels.begin();
        } else {
            mActiveModel = nullptr;
        }
    }
}
//
//  We are not doing the cleanup in the destructor as it does not allow us
//  intervention if someone decides different in the dialogs presented.
void PMApp::doExit() {
    bool do_exit = true;

    for (auto model : mModels) {
        //
        //  Ask for saving for each modified model.
        if (model->isModified()) {

        }
    }
    //
    //  Maybe some decides different while closing the models. Then do_exit
    //  shall be false.
    if (do_exit == true) {
        mMainWindow.close();
    }
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
    mModels.insert(mActiveModel = new PMModel(aPath));
    return retval;
}
//
//  This is a public version of the doNew() private signal processing method.
//  Its because to keep signal processing seperate from simple interfacing to other
//  classes. Here only to the main module.
void PMApp::EmptyInit() {
    doNew();
}

