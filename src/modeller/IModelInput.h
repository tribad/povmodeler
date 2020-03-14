// *************************************************************************************************************
//
//  Modul-Name     : IModelInput.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef IMODELINPUT_INC
#define IMODELINPUT_INC
//
//  This is the class
class IModelInput {
public:
    IModelInput() = default;
    virtual ~IModelInput() = default;
    virtual void LoadKpovModelerFile(QString aFileName) ;
};

#endif  // IMODELINPUT_INC
