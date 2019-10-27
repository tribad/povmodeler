// **************************************************************************
//
// Modul-Name        : sigpmviewmenu.cpp
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 22.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
//
//
//  Mix-In classes
#include "ipmviewmenu.h"
//
//  Local includes.
#include "sigpmviewmenu.h"

SigPMViewMenu::SigPMViewMenu(QObject *parent) : QObject(parent)
{

}
SigPMViewMenu::SigPMViewMenu(IPMViewMenu* ifc, QObject *parent) : QObject(parent)
{
    mIfc = ifc;
}
//
//  Slots
void SigPMViewMenu::slotProperty(bool changed) {
}
void SigPMViewMenu::slotTop(bool changed) {
    mIfc->toggleGlViewVisibility(GLView::Top,  changed);
}
void SigPMViewMenu::slotBottom(bool changed) {
    mIfc->toggleGlViewVisibility(GLView::Bottom,  changed);
}
void SigPMViewMenu::slotLeft(bool changed) {
    mIfc->toggleGlViewVisibility(GLView::Left,  changed);
}
void SigPMViewMenu::slotRight(bool changed) {
    mIfc->toggleGlViewVisibility(GLView::Right,  changed);
}
void SigPMViewMenu::slotBack(bool changed) {
    mIfc->toggleGlViewVisibility(GLView::Back,  changed);
}
void SigPMViewMenu::slotFront(bool changed) {
    mIfc->toggleGlViewVisibility(GLView::Front,  changed);
}
void SigPMViewMenu::slotCamera(bool changed) {
    mIfc->toggleGlViewVisibility(GLView::Camera,  changed);
}
