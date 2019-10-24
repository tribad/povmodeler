// **************************************************************************
//
// Modul-Name        : sigpmtreewidget.cpp
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 23.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************

#include "sigpmtreewidget.h"

SigPMTreeWidget::SigPMTreeWidget(QWidget *parent) : QTreeView(parent)
{

}

QSize SigPMTreeWidget::sizeHint() const {
    return QSize(300,300);
}
