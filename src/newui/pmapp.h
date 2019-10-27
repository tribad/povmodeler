// **************************************************************************
//
// Modul-Name        : pmapp.h
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 22.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
#ifndef PMAPP_H
#define PMAPP_H
//
//  System header
#include <set>
//
//  Qt additional header
#include <QObject>
#include <QMainWindow>
//  UI includes
#include "ui_pmmainwindow.h"
//
//  Interface classes
#include "ipmviewmenu.h"
#include "ipmfilemenu.h"
//
//  Signal handler
#include "sigpmviewmenu.h"
#include "sigpmfilemenu.h"
//
//  Other member includes
#include "pmrecentfilelist.h"
//
//  povray model includes
#include "pmmodel.h"

class PMApp : public QObject, public IPMViewMenu, IPMFileMenu
{
    Q_OBJECT
public:
    explicit PMApp(QObject *parent = nullptr);
    virtual ~PMApp() {}
    //
    //  External interface. Mostly to the main.cpp
    bool Load(const QString& aPath);
    void EmptyInit();
signals:

public slots:
    //
    //  Tree widget interface
    void selectedInTree(const QModelIndex& index);
    //
    //  Recentfile sub-menu
    void doLoadRecent(QAction* recentAction);
private:  //  Methods
    //
    // View menu interface
    virtual void togglePropertyViewVisibility(bool changed);
    virtual void toggleGlViewVisibility(GLView view, bool changed);
    //
    // GLView interface
    virtual void setGlViewChecked(GLView view, bool checked);
    //
    // File Menu interface.
    virtual void doNew();
    virtual void doLoad();
    virtual void doSave();
    virtual void doClose();
    virtual void doExit();
    //
    //  File menu internal handling.
    virtual void setupRecentFileMenu();
    virtual void updateRecentFilesMenu();

public:   //  Attributes
private:  //  Attributes
    //
    //  Main window and all dynamics
    QMainWindow           mMainWindow;
    Ui_MainWindow         mPMMainWindow;
    //
    //  Recent files submenu
    QMenu                 mRecentFilesMenu;
    //
    //  Local signal handler
    SigPMViewMenu*        mSigPMViewMenu;
    SigPMFileMenu*        mSigPMFileMenu;
    //
    //  Application data.
    PMRecentFileList      mRecentFiles;
    PMModel*              mActiveModel;
    //
    //  Using a set here makes it easier to remove a model by its pointer.
    std::set<PMModel*>    mModels;
};

#endif // PMAPP_H
