// *************************************************************************************************************
//
//  Modul-Name     : CModelStoreThread.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef CMODELSTORETHREAD_INC
#define CMODELSTORETHREAD_INC
//
//  This is the class
class CModelStoreThread : public CMsgThread {
public:
    virtual ~CModelStoreThread() = default;
    CModelStoreThread(IIncomingMessages& aIncomingMessage) ;
    virtual void Process(tMsg* aMsg) ;
public:
    IIncomingMessages& mMsgToModeller;
private:
    CSimIfc*           mStoreIfc;
};
extern CCoreIfc* __coreIfc;

#endif  // CMODELSTORETHREAD_INC
