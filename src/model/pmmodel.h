// **************************************************************************
//
// Modul-Name        : pmmodel.h
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 23.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
#ifndef PMMODEL_H
#define PMMODEL_H
//
//  Include Qt specifcs
#include <QObject>
//
//  This is a container to hold all povmodeler specific support classes needed
//  in the model tree. Its a replacement for the former PMPart class. But this is
//  smaller and should help remove direct dependencies to the UI elements.
class PMModel : public QObject
{
    Q_OBJECT
public:
    explicit PMModel(QObject *parent = nullptr);

signals:

public slots:
private:  //  attributes

};

#endif // PMMODEL_H
