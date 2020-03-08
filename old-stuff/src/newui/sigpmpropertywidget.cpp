// **************************************************************************
//
// Modul-Name        : sigpmpropertywidget.cpp
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 23.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************

#include "sigpmpropertywidget.h"

SigPMPropertyWidget::SigPMPropertyWidget(QWidget *parent) : QWidget(parent)
{

}
QSize SigPMPropertyWidget::sizeHint() const {
    return QSize(300,300);
}
