#include "coreifc.h"

void simaddobject(tSimObj*);
void simdelobject(tSimObj*);
void simaddmsg(tMsg *msg) ;
void simaddsig(tSig *sig) ;

CCoreIfc::CCoreIfc()
{

}

CCoreIfc::~CCoreIfc() {

}

void CCoreIfc::StartObject(tSimObj *obj) {
    //simaddobject(obj);
}

void CCoreIfc::FreeObject(tSimObj *obj) {
    //simdelobject(obj);
}

void CCoreIfc::ScheduleMsg(tMsg *aMsg, uint64_t aDelay) {
    //simaddmsg(aMsg);
}

void CCoreIfc::ScheduleSignal(tSig *aSig, uint64_t aDelay) {
    //simaddsig(aSig);
}
