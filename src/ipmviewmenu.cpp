// **************************************************************************
//
// Modul-Name        : ipmviewmenu.cpp
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 22.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
//
//
//  Mix-In classes
#include "mpmviewmenu.h"
//
//  Local includes.
#include "ipmviewmenu.h"

IPMViewMenu::IPMViewMenu(QObject *parent) : QObject(parent)
{

}
IPMViewMenu::IPMViewMenu(MPMViewMenu* mix, QObject *parent) : QObject(parent)
{
    mMixIn = mix;
}
//
//  Slots
void IPMViewMenu::slotProperty(bool changed) {
}
void IPMViewMenu::slotTop(bool changed) {
    mMixIn->toggleGlView(GLView::Top,  changed);
}
void IPMViewMenu::slotBottom(bool changed) {
    mMixIn->toggleGlView(GLView::Bottom,  changed);
}
void IPMViewMenu::slotLeft(bool changed) {
    mMixIn->toggleGlView(GLView::Left,  changed);
}
void IPMViewMenu::slotRight(bool changed) {
    mMixIn->toggleGlView(GLView::Right,  changed);
}
void IPMViewMenu::slotBack(bool changed) {
    mMixIn->toggleGlView(GLView::Back,  changed);
}
void IPMViewMenu::slotFront(bool changed) {
    mMixIn->toggleGlView(GLView::Front,  changed);
}
void IPMViewMenu::slotCamera(bool changed) {
    mMixIn->toggleGlView(GLView::Camera,  changed);
}
