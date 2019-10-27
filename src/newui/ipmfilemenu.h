// **************************************************************************
//
// Modul-Name        : ipmfilemenu.h
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 24.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************

#ifndef IPMFILEMENU_H
#define IPMFILEMENU_H


class IPMFileMenu
{
public:
    IPMFileMenu();
    virtual ~IPMFileMenu() {}
    virtual void doNew() = 0;
    virtual void doLoad() = 0;
    virtual void doSave() = 0;
    virtual void doClose() = 0;
    virtual void doExit() = 0;
};

#endif // IPMFILEMENU_H
