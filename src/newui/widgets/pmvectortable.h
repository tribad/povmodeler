// **************************************************************************
//
// Modul-Name        : pmvectortable.h
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 25.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************

#ifndef PMVECTORTABLE_H
#define PMVECTORTABLE_H

#include <QTableWidget>

namespace widget {

class PMVectorTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit PMVectorTable(QWidget* parent);
};


}

#endif // PMVECTORTABLE_H
