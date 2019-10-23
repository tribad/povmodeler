// **************************************************************************
//
// Modul-Name        : ipmviewmenu.h
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 22.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
#ifndef IPMVIEWMENU_H
#define IPMVIEWMENU_H
//
//  Qt additional header
#include <QObject>
//
//  Mix-In classes
#include "mpmviewmenu.h"

class IPMViewMenu : public QObject
{
    Q_OBJECT
public:
    explicit IPMViewMenu(QObject *parent = nullptr);
    explicit IPMViewMenu(MPMViewMenu* mix, QObject *parent = nullptr);

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
    MPMViewMenu* mMixIn;
};

#endif // IPMVIEWMENU_H
