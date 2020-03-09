#ifndef MSGQUEUE_H
#define MSGQUEUE_H

#include <list>
#include <msg.h>
#include <CEvent.h>

class CMsgQueue : public CEvent
{
public:
    CMsgQueue();
    virtual ~CMsgQueue();
    void Put(tMsg* msg);
    void PutBack(tMsg* msg);
    tMsg* Get(void);
    //
    //  This is the queue checker for the event base class.
    virtual bool CheckCondition();
private:
    std::list<tMsg*>     msgqueue;
};

#endif // MSGQUEUE_H
