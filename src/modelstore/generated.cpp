#include "generated.h"
#include <simobjfactory.h>


CPointerIndex simidx;
CLogger       simlog(ModulId::SimulationLib, "");

tSimObj* NewObjectFromTemplate(uint64_t tid, uint64_t templ, tSimObj *parent) {
    tSimObj* retval = 0;

    retval = factory_createfromtemplate(tid, templ, 0);
    if (retval != 0) {
        retval->parent = parent;
        retval->objid  = INVALID_OBJID;
        simidx.Add(retval);
    } else {
    }
 
     return retval;
 }
 
tSimObj* NewObject(uint64_t tid, tSimObj *parent) {
    tSimObj* retval = 0;
 
    uint64_t newobjid = simidx.Reserve();
    retval = factory_createnewobj(tid, newobjid);
    if (retval != 0) {
        retval->parent = parent;
        simidx.Add(retval);
    } else {
    }
 
     return retval;
}
