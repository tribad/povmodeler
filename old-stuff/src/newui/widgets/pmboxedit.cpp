// **************************************************************************
//
// Modul-Name        : pmboxedit.cpp
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 25.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
#include "ui_boxedit.h"
#include "pmboxedit.h"

static Ui::BoxEdit boxedit_base;

widget::PMBoxEdit::PMBoxEdit(QWidget *parent) : PMEditBase(parent)
{
    boxedit_base.setupUi(this);
    boxedit_base.tableWidget->setRowCount(2);
    boxedit_base.tableWidget->setVerticalHeaderItem(0, new QTableWidgetItem("Corner 1"));
    boxedit_base.tableWidget->setVerticalHeaderItem(1, new QTableWidgetItem("Corner 2"));

    boxedit_base.tableWidget->SetFontSize(9);
}

void widget::PMBoxEdit::SetupData(PMObject *aObject) {
    boxedit_base.lineEdit->setText(aObject->property("name").asString());
    boxedit_base.tableWidget->Set (0, aObject->property("corner1"));
    boxedit_base.tableWidget->Set (1, aObject->property("corner2"));
}
