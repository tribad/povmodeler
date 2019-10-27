// **************************************************************************
//
// Modul-Name        : sigpmfilemenu.cpp
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 24.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************

#include "sigpmfilemenu.h"
#include "ipmfilemenu.h"

SigPMFileMenu::SigPMFileMenu(QObject *parent) : QObject(parent)
{

}

SigPMFileMenu::SigPMFileMenu(IPMFileMenu* ifc, QObject *parent) : QObject(parent)
{
    mIfc = ifc;
}

void SigPMFileMenu::slotNew() {
    mIfc->doNew();
}
void SigPMFileMenu::slotLoad() {
    mIfc->doLoad();
}
void SigPMFileMenu::slotSave() {
    mIfc->doSave();
}
void SigPMFileMenu::slotClose() {
    mIfc->doClose();
}
void SigPMFileMenu::slotExit() {
    mIfc->doExit();
}
