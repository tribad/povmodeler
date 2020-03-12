// *************************************************************************************************************
//
//  Modul-Name     : IIncomingMessages.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef IINCOMINGMESSAGES_INC
#define IINCOMINGMESSAGES_INC
//
//  This is the class
class IIncomingMessages {
public:
    IIncomingMessages() = default;
    virtual ~IIncomingMessages() = default;
    virtual void Process(tMsg* aMsg) ;
};

#endif  // IINCOMINGMESSAGES_INC
