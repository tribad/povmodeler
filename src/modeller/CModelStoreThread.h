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
    ~CModelStoreThread() = default;
    CModelStoreThread() ;
    static CModelStoreThread& GetInstance(void) ;
private:
    CSimIfc* mStoreIfc;
};
extern CCoreIfc* __coreIfc;

#endif  // CMODELSTORETHREAD_INC
