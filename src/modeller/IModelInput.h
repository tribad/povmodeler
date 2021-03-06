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
    virtual ~IModelInput() = default;
    virtual void LoadKpovModelerFile(QString aFileName) = 0;
};

#endif  // IMODELINPUT_INC
