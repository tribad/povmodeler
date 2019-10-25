#include <QFile>
#include <QIcon>

#include "pmscene.h"
#include "pmmodel.h"
#include "pmxmlparser.h"

PMModel::PMModel(QObject *parent) : QAbstractItemModel(parent)
{
    mModified = false;
    mScene    = nullptr;
    mPath     = "unnamed";
}

PMModel::PMModel(const QString& aPath, QObject *parent) : PMModel(parent)
{
    Load(aPath);
}

//
//  Implementation of the pure virtuals from QAbstractItemModel
QModelIndex PMModel::index(int row, int column, const QModelIndex &parent) const {
    QModelIndex retval;
    //
    //  As we use the pointers to the PMObjects in the tree here,
    //  we can check it to identify the root object.
    if (parent.internalPointer() == nullptr) {
        retval = createIndex(0,0,static_cast<void*>(mScene));
    } else {
        PMObject* parentnode = static_cast<PMObject*>(parent.internalPointer());

        retval = createIndex(row, 0, static_cast<void*>(parentnode->childAt(row)));
    }
    return retval;
}
QModelIndex PMModel::parent(const QModelIndex &index) const {
    QModelIndex retval;
    //
    // Security check against malformed index.
    if (index.internalPointer() != nullptr) {
        PMObject* indexed = static_cast<PMObject*>(index.internalPointer());
        //
        //  This is the pointer we need to return
        PMObject* parentptr = indexed->parent();
        int       parentrow = -1;                 //  Initial for root
        //
        //  To get the row-number for the parent we need the parents
        //  parent. But if the parentptr == nullptr we on the root.
        if (parentptr != nullptr) {
            PMObject* parentparentptr = parentptr->parent();
            //
            //  if parentparentptr == nullptr parent is the root. So we set 0
            //  as row
            if (parentparentptr != nullptr) {
                parentrow = parentparentptr->findChild(parentptr);
            } else {
                parentrow = 0;
            }
            retval = createIndex(parentrow, 0, static_cast<void*>(parentptr));
        }
    }

    return retval;
}
//
//  This method returns the number of children of an item.
//  For the root node we do have only one item, the scene.
//  This is obvious valid until we allow multiple scenes in a model.
int PMModel::rowCount(const QModelIndex &parent) const {
    int retval = 1;
    //
    //  As we use the pointers to the PMObjects in the tree here,
    //  we can check it to identify the root object.
    if (parent.internalPointer() == nullptr) {

    } else {
        PMObject* parentnode = static_cast<PMObject*>(parent.internalPointer());

        retval = parentnode->countChildren();
    }
    return retval;
}
//
//  For now we do have only a single column. But that may change.
int PMModel::columnCount(const QModelIndex &parent) const {
    int retval = 1;

    return retval;
}

QVariant PMModel::data(const QModelIndex &index, int role) const {
    QVariant retval;
    PMObject* item = static_cast<PMObject*>(index.internalPointer());

    if (item != nullptr) {
        if (role == Qt::DisplayRole) {
                if (!item->name().isEmpty()) {
                    retval = item->name();
                } else {
                    retval = item->className();
                }
        } else if (role == Qt::DecorationRole) {
            QString iconpath = ":/smallicon/icons/povicons/small/pm" + item->className();
            retval = QIcon( iconpath.toLower());
        }
    }
    return retval;
}
//
//  Some basic methods to handle with a model.
bool PMModel::Load(const QString& aPath) {
    PMObjectList list;
    QIODevice*   dev     = new QFile( aPath );
    bool         success = true;
    //
    //  Save the path to have it available for storing.
    mPath = aPath;

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

bool PMModel::Store(const QString& aPath) {
    bool retval = false;

    return retval;
}
//
//  This will fill the model with some default elements.
//  Important point is, that the modified flag shall stay false (unmodified)
void PMModel::FillWithDefault() {
    mModified = false;
}
