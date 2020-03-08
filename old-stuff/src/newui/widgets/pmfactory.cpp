// **************************************************************************
//
// Modul-Name        : pmfactory.cpp
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 25.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************

#include "pmfactory.h"
#include "pmboxedit.h"

widget::PMFactory::PMFactory()
{

}

widget::PMEditBase* widget::PMFactory::Create(const QString &aWidgetName) {
    widget::PMEditBase* retval = nullptr;

    if (aWidgetName == "Box") {
        retval = new widget::PMBoxEdit();
    }
    return retval;
}
