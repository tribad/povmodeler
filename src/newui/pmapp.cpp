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
#include <QFileDialog>
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
    setupRecentFileMenu();
    //
    // others.
    mActiveModel = nullptr;
    mRecentFiles.Load();
    updateRecentFilesMenu();
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
    mPMMainWindow.dockWidgetContents->expand(mActiveModel->GetRootIndex());
}
void PMApp::doLoad() {
    //
    //  Get the last visited from the settings.
    //  If not set already we take the users home directory.
    QString last_visited = PMSettings::instance().value(LAST_DIRECTORY_VISITED, QDir::homePath()).toString();

    QString to_open = QFileDialog::getOpenFileName(nullptr, "Open File", last_visited, "POV modeler (*.kpm)");
    //
    //  If the user selected a file we do open it.
    //  This also updates the recent file list.
    if (!to_open.isEmpty()) {
        Load(to_open);
        //
        //  Convenient way to get the directory where the file resides.
        QFileInfo now_visited(to_open);

        PMSettings::instance().setValue(LAST_DIRECTORY_VISITED, now_visited.absolutePath());
    }
}

void PMApp::doLoadRecent(QAction *recentAction) {
    if (recentAction != nullptr) {
        //
        //  If the load failed we remove the file name from the recent files list.
        //  On sucessfull load it is all done in the Load() method.
        if (!Load(recentAction->text())) {
            mRecentFiles.Remove(recentAction->text());
            updateRecentFilesMenu();
        }
    }
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
//  setup the recent file menu into the right position within the file menu.
//  This would be direct beneath the open action.
void PMApp::setupRecentFileMenu() {
    QList<QAction*> actions    =  mPMMainWindow.menuFile->actions();
    //
    //  We are searching the original action setup in the designer as placeholder.
    for (auto before = actions.begin(); before != actions.end(); ++before) {
        if ((*before)->text() == "Open Recent ...") {
            if (before != actions.end()) {
                //
                //  Copying the text and icon from the original action.
                //  This way we can change the search to something that is less bound
                //  to the action->text()
                mRecentFilesMenu.menuAction()->setText( (*before)->text());
                mRecentFilesMenu.menuAction()->setIcon( (*before)->icon() );
                //
                //  Replace the action.
                mPMMainWindow.menuFile->insertMenu(*before, &mRecentFilesMenu);
                mPMMainWindow.menuFile->removeAction(*before);
            }
            break;
        }
    }
    connect(&mRecentFilesMenu, SIGNAL(triggered(QAction*)), this, SLOT(doLoadRecent(QAction*)));
}
//
//  Update the recentfile menu.
void PMApp::updateRecentFilesMenu() {
    std::list<QString> fl = mRecentFiles.GetFiles();
    //
    //  Hopefully removing all memory used by actions as well.
    mRecentFilesMenu.clear();
    //
    //  File the actions
    for (auto f : fl) {
        if (!f.isEmpty()) {
            mRecentFilesMenu.addAction(f);
        }
    }
}
//
//  Initialization
bool PMApp::Load(const QString& aPath) {
    bool retval = false;
    //
    //  We may throw an exception if the load fails and then return false.
    //  But for now we check the pointer to the scene within the model
    //  with the isEmpty() method on the model.
    PMModel* new_model = new PMModel(aPath);

    if (!new_model->isEmpty()) {
        //
        //  Setting the active model to the new loaded one in a hurry.
        mModels.insert(mActiveModel = new_model);
        //
        //  Attach the model to the tree view
        mPMMainWindow.dockWidgetContents->setModel(mActiveModel);
        mPMMainWindow.dockWidgetContents->expand(mActiveModel->GetRootIndex());
        //
        //  Put the file to the recent file list and update the menu.
        mRecentFiles.SetFile(aPath);
        updateRecentFilesMenu();
        //
        //  Convenient way to get the directory where the file resides.
        QFileInfo now_visited(aPath);

        mMainWindow.setWindowTitle(now_visited.baseName() + " - povmodeler");
        retval = true;
    }

    return retval;
}
//
//  This is a public version of the doNew() private signal processing method.
//  Its because to keep signal processing seperate from simple interfacing to other
//  classes. Here only to the main module.
void PMApp::EmptyInit() {
    doNew();
}

