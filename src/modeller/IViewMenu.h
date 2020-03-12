// *************************************************************************************************************
//
//  Modul-Name     : IViewMenu.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef IVIEWMENU_INC
#define IVIEWMENU_INC
#include <QObject>
//
//  This is the class
class IViewMenu : public QObject {
Q_OBJECT
public:
    IViewMenu() = default;
    virtual ~IViewMenu() = default;
public slots:
    void Explorer(bool aState) ;
    void Property(bool aState) ;
    void Top(bool aState) ;
    void Bottom(bool aState) ;
    void Left(bool aState) ;
    void Right(bool aState) ;
    void Front(bool aState) ;
    void Back(bool aState) ;
    void Camera(bool aState) ;
    void Live(bool aState) ;
};

#endif  // IVIEWMENU_INC
