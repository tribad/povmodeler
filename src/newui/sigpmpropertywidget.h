// **************************************************************************
//
// Modul-Name        : sigpmpropertywidget.h
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 23.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************

#ifndef SIGPMPROPERTYWIDGET_H
#define SIGPMPROPERTYWIDGET_H

#include <QWidget>

class SigPMPropertyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SigPMPropertyWidget(QWidget *parent = nullptr);
    virtual QSize sizeHint() const;

signals:

public slots:
};

#endif // SIGPMPROPERTYWIDGET_H
