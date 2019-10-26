// **************************************************************************
//
// Modul-Name        : pmvectortable.cpp
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 25.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
#include <QHeaderView>

#include "pmvariant.h"
#include "pmvectortable.h"

widget::PMVectorTable::PMVectorTable(QWidget* parent) : QTableWidget(parent)
{
    setColumnCount(3);
    setRowCount(1);
    setHorizontalHeaderItem(0, new QTableWidgetItem("X"));
    setHorizontalHeaderItem(1, new QTableWidgetItem("Y"));
    setHorizontalHeaderItem(2, new QTableWidgetItem("Z"));
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void widget::PMVectorTable::SetFontSize(int size) {
    QFont font = horizontalHeaderItem(0)->font();

    font.setPointSize(size);
    horizontalHeaderItem(0)->setData(Qt::FontRole, font);
    horizontalHeaderItem(1)->setData(Qt::FontRole, font);
    horizontalHeaderItem(2)->setData(Qt::FontRole, font);
    for (int r = 0; r < rowCount(); ++r) {
        verticalHeaderItem(r)->setData(Qt::FontRole, font);
        for (int c = 0; c < columnCount(); ++c) {
            if (item(r, c) != nullptr) {
                item(r, c)->setData(Qt::FontRole, font);
            }
        }
    }
    resizeRowsToContents();
}

void widget::PMVectorTable::Set(int row, const PMVariant &aValue) {
    PMVector v = aValue.vectorData();

    for (auto x = 0; x < 3; ++x) {
        if (item (row, x) == nullptr) {
            setItem (row, x, new QTableWidgetItem);
        }
    }
    QString a;

    double d = v.x();

    item (row, 0)->setText( QString::number( v.x()) );
    item (row, 1)->setText(  QString::number( v.y())  );
    item (row, 2)->setText(  QString::number( v.z())  );
}
