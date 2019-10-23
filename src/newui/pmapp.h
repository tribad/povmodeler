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
//
//  Signal handler
#include "sigpmviewmenu.h"

class PMApp : public QObject, public IPMViewMenu
{
    Q_OBJECT
public:
    explicit PMApp(QObject *parent = nullptr);
    virtual ~PMApp() {}
signals:

public slots:
private:  //  Methods
    //
    // View Menu mixins
    virtual void togglePropertyVisibility(bool changed);
    virtual void toggleGlViewVisibility(GLView view, bool changed);
    //
    // GLView mixins
    virtual void setGlViewChecked(GLView view, bool checked);
public:   //  Attributes
private:  //  Attributes
    QMainWindow     mMainWindow;
    Ui_MainWindow   mPMMainWindow;
    SigPMViewMenu*  mSigPMViewMenu;
};

#endif // PMAPP_H
