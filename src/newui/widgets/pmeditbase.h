// **************************************************************************
//
// Modul-Name        : pmbaseedit.h
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 26.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************

#ifndef PMEDITBASE_H
#define PMEDITBASE_H

#include <QWidget>
#include "pmobject.h"

namespace widget {

class PMEditBase : public QWidget
{
    Q_OBJECT
public:
    explicit PMEditBase(QWidget *parent = nullptr);

    virtual ~PMEditBase() {}
    virtual void SetupData(PMObject* aObject) = 0;
};

}
#endif // PMEDITBASE_H
