// **************************************************************************
//
// Modul-Name        : pmboxedit.h
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 25.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************

#ifndef PMBOXEDIT_H
#define PMBOXEDIT_H

#include <QWidget>
#include "pmeditbase.h"
#include "pmobject.h"

namespace widget {

class PMBoxEdit : public PMEditBase
{
    Q_OBJECT
public:
    PMBoxEdit(QWidget *parent = nullptr);
    virtual void SetupData(PMObject* aObject);
signals:

public slots:

private:
};
}

#endif // PMBOXEDIT_H
