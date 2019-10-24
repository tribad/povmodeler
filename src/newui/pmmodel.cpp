#include <QFile>

#include "pmscene.h"
#include "pmmodel.h"
#include "pmxmlparser.h"

PMModel::PMModel(QObject *parent) : QAbstractItemModel(parent)
{
    mModified = false;
    mScene    = nullptr;
}

PMModel::PMModel(const QString& aPath, QObject *parent) : PMModel(parent)
{
    Load(aPath);
}

bool PMModel::Load(const QString& aPath) {
    PMObjectList list;
    QIODevice* dev = new QFile( aPath );
    bool success = true;


    if( dev && dev->open( QIODevice::ReadOnly ) )
    {
        PMXMLParser parser( dev );
        parser.parse( &list, nullptr, nullptr );//step1

        PMObject* obj = list.first();
        if( obj )
        {
            if( obj->type() == "Scene" ) {
                mScene = static_cast<PMScene*>(obj);
            } else {
                success = false;
            }
        } else {
            success = false;
        }
    }
    return success;
}
//
//  Implementation of the pure virtuals from QAbstractItemModel
QModelIndex PMModel::index(int row, int column, const QModelIndex &parent) const {
    QModelIndex retval;
    return retval;
}
QModelIndex PMModel::parent(const QModelIndex &index) const {
    QModelIndex retval;

    return retval;
}
int PMModel::rowCount(const QModelIndex &parent) const {
    int retval = 0;
    return retval;
}
int PMModel::columnCount(const QModelIndex &parent) const {
    int retval = 0;

    return retval;
}
QVariant PMModel::data(const QModelIndex &index, int role) const {
    QVariant retval;

    return retval;
}

