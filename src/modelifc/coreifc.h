#ifndef COREIFC_H
#define COREIFC_H

#include <simobj.h>

class CMsgQueue;

class CCoreIfc
{
public:
    CCoreIfc();
    virtual ~CCoreIfc();
    //
    //  StartObject puts the object into the Update-Tables to let
    //  it run in a time-discret fashion.
    //  The itself decides if and when it needs no further updates.
    virtual void StartObject(tSimObj* obj);
    //
    //  FreeObject removes the object from the simulation and frees the
    //  associated memory, but only for the object itself.
    //  This means not that the object gets deleted from the DB. This function
    //  is needed to manage the memory and may be called even for objects that are
    //  loaded on demand and are not further on needed.
    virtual void FreeObject(tSimObj* obj);
    //
    //  Adding a signal into the schedule table so that they can be processed within
    //  a cycle or with a delay.
    virtual void ScheduleSignal(tSig* aSig, uint64_t aDelay = 0u);
    //
    //  Adding a messagec into the schedule table so that they can be processed within
    //  a cycle or with a delay.
    virtual void ScheduleMsg(tMsg* aMsg, uint64_t aDelay = 0u);
public:
    //
    //  List of message queues to the important components of the core.
    CMsgQueue *stdb;       //  To the database that stores the simulation objects
    int        stdbhandle; //  The handle to the stdb
    CMsgQueue *pgdb;       //  To the postgresql db interface
    CMsgQueue *mariadb;    //  To the mariadb interface
    CMsgQueue *comm;       //  To the comm thread (dispatching messages)
    //
    //  Cycle Counter. Within a cycle they do not change.
    //  But maybe they get changed from different threads.
    volatile uint64_t   relCycle;   //  Cycle count from startup not settable
    volatile uint64_t   absCycle;   //  Cycle count in absolut value. Can be changed from the simulation.
};

#endif // COREIFC_H
