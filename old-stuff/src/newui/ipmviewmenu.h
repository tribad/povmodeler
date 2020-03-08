// **************************************************************************
//
// Modul-Name        : ipmviewmenu.h
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 22.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
#ifndef IPMVIEWMENU_H
#define IPMVIEWMENU_H
//
//  Only to have a clou what gl-view has been toggled.
enum class GLView {
    Top,
    Bottom,
    Left,
    Right,
    Back,
    Front,
    Camera,
    Undefined
};
//
//  Interface to the class that does the processing.
class IPMViewMenu
{
public:
    IPMViewMenu();
    virtual ~IPMViewMenu() {}
    virtual void togglePropertyViewVisibility(bool changed) = 0;
    virtual void toggleGlViewVisibility(GLView view, bool changed) = 0;
};

#endif // IPMVIEWMENU_H
