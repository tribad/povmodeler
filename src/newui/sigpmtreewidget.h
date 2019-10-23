// **************************************************************************
//
// Modul-Name        : sigpmtreewidget.h
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 23.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
#ifndef SIGPMTREEWIDGET_H
#define SIGPMTREEWIDGET_H
//
// Qt includes
#include <QTreeWidget>

class SigPMTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit SigPMTreeWidget(QWidget *parent = nullptr);
    //explicit SigPMTreeWidget(IPMViewMenu* ifc, QObject *parent = nullptr);
    virtual QSize sizeHint() const;
};

#endif // SIGPMTREEWIDGET_H
