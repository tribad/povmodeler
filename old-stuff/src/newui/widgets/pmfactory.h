// **************************************************************************
//
// Modul-Name        : pmfactory.h
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 25.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************

#ifndef PMFACTORY_H
#define PMFACTORY_H

#include <QWidget>

#include "pmeditbase.h"

namespace widget {

class PMFactory
{
public:
    PMFactory();
    ~PMFactory() {}
    static widget::PMEditBase* Create(const QString& aWidgetName);
};

}
#endif // PMFACTORY_H
