// **************************************************************************
//
// Modul-Name        : sigpmfilemenu.h
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 24.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************

#ifndef SIGPMFILEMENU_H
#define SIGPMFILEMENU_H

#include <QObject>

class IPMFileMenu;

class SigPMFileMenu : public QObject
{
    Q_OBJECT
public:
    explicit SigPMFileMenu(QObject *parent = nullptr);
    explicit SigPMFileMenu(IPMFileMenu* ifc, QObject *parent = nullptr);

signals:

public slots:
    void slotNew();
    void slotLoad();
    void slotSave();
    void slotClose();
    void slotExit();
private:
    IPMFileMenu* mIfc;
};

#endif // SIGPMFILEMENU_H
