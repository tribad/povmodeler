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
#include <QAbstractItemModel>
//
//  PM forwards
class PMScene;
//
//  The class defintion
class PMModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit PMModel(QObject *parent = nullptr);
    explicit PMModel(const QString& aPath,QObject *parent = nullptr);
    //
    //  Some implementations for pure virtuals from QAbstractItemModel
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &index) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    //
    //  Some basic methods
    bool Load(const QString& aPath);
    bool Store(const QString& aPath);
    //
    //  Getters.
    bool isModified() {return mModified;}

signals:

public slots:
public: //  attributes

private:  //  attributes
    QString  mPath;
    bool     mModified;
    PMScene* mScene;
};

#endif // PMMODEL_H
