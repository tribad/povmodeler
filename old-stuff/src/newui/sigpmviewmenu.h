// **************************************************************************
//
// Modul-Name        : sigpmviewmenu.h
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 22.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
#ifndef SIGPMVIEWMENU_H
#define SIGPMVIEWMENU_H
//
//  Qt additional header
#include <QObject>
//
//  interface classes
#include "ipmviewmenu.h"

class SigPMViewMenu : public QObject
{
    Q_OBJECT
public:
    explicit SigPMViewMenu(QObject *parent = nullptr);
    explicit SigPMViewMenu(IPMViewMenu* ifc, QObject *parent = nullptr);

signals:

public slots:
    void slotProperty(bool checked);
    void slotTop(bool checked);
    void slotBottom(bool checked);
    void slotLeft(bool checked);
    void slotRight(bool checked);
    void slotBack(bool checked);
    void slotFront(bool checked);
    void slotCamera(bool checked);
private:
    IPMViewMenu* mIfc;
};

#endif // SIGPMVIEWMENU_H
