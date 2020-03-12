// *************************************************************************************************************
//
//  Modul-Name     : IEditMenu.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef IEDITMENU_INC
#define IEDITMENU_INC
#include <QObject>
//
//  This is the class
class IEditMenu : public QObject {
Q_OBJECT
public:
    IEditMenu() = default;
    virtual ~IEditMenu() = default;
public slots:
    void Cut(void) ;
    void Copy(void) ;
    void Paste(void) ;
    void Delete(void) ;
    void Undo(void) ;
    void Redo(void) ;
};

#endif  // IEDITMENU_INC
