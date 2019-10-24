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
//  PM forwards
class PMScene;
//
//  The class defintion
class PMModel : public QObject
{
    Q_OBJECT
public:
    explicit PMModel(QObject *parent = nullptr);
    explicit PMModel(const QString& aPath,QObject *parent = nullptr);
    //
    //  Some basic methods
    bool Load(const QString& aPath);
    //
    //  Getters.
    bool isModified() {return mModified;}

signals:

public slots:
public: //  attributes

private:  //  attributes
    bool     mModified;
    PMScene* mScene;
};

#endif // PMMODEL_H
