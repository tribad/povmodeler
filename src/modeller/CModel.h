// *************************************************************************************************************
//
//  Modul-Name     : CModel.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef CMODEL_INC
#define CMODEL_INC
//
//  This is the class
class CModel : public IModelInput, public IIncomingMessages {
public:
    virtual ~CModel() = default;
    CModel(IGUIInput& aGUIInput, CMsgQueue& aOutgoingMessage) ;
};

#endif  // CMODEL_INC
