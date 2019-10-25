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
#include "ui_boxedit.h"

Ui::BoxEdit boxedit;

widget::PMFactory::PMFactory()
{

}

QWidget* widget::PMFactory::Create(const QString &aWidgetName) {
    QWidget* retval = nullptr;

    if (aWidgetName == "Box") {
        retval = new QWidget;
        boxedit.setupUi(retval);
    }
    return retval;
}
