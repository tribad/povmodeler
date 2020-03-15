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
    ~IIncomingMessages() = default;
    virtual void Process(tMsg* aMsg) = 0;
};

#endif  // IINCOMINGMESSAGES_INC
