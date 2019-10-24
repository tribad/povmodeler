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
//  povray model includes
#include "pmmodel.h"

class PMApp : public QObject, public IPMViewMenu, IPMFileMenu
{
    Q_OBJECT
public:
    explicit PMApp(QObject *parent = nullptr);
    virtual ~PMApp() {}
    bool Load(const QString& aPath);
signals:

public slots:
private:  //  Methods
    //
    // View menu interface
    virtual void togglePropertyViewVisibility(bool changed);
    virtual void toggleGlViewVisibility(GLView view, bool changed);
    //
    // GLView interface
    virtual void setGlViewChecked(GLView view, bool checked);
    //
    //
    virtual void doNew();
    virtual void doLoad();
    virtual void doSave();
    virtual void doClose();
    virtual void doExit();
public:   //  Attributes
private:  //  Attributes
    //
    //  Main window
    QMainWindow           mMainWindow;
    Ui_MainWindow         mPMMainWindow;
    //
    //  Local signal handler
    SigPMViewMenu*        mSigPMViewMenu;
    SigPMFileMenu*        mSigPMFileMenu;
    //
    //  Application data.
    PMModel*              mActiveModel;
    std::vector<PMModel*> mModels;
};

#endif // PMAPP_H
