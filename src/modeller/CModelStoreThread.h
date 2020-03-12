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
//  List of forwards needed in this module.
class IIncomingMessages;
//
//  This is the class
class CModelStoreThread : public CMsgThread {
public:
    virtual ~CModelStoreThread() = default;
    CModelStoreThread() ;
    static CModelStoreThread& GetInstance(void) ;
    virtual void Process(tMsg* aMsg) ;
private:
    IIncomingMessages* mMsgToModeller;
    CSimIfc*           mStoreIfc;
};
extern CCoreIfc* __coreIfc;

#endif  // CMODELSTORETHREAD_INC
