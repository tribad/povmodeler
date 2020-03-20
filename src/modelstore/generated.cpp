#include "generated.h"
#include <simobjfactory.h>


CPointerIndex simidx;
CLogger       simlog(ModulId::SimulationLib, "");

tSimObj* NewObjectFromTemplate(uint64_t tid, uint64_t templ, tSimObj *parent, bool doInit) {
    tSimObj* retval = 0;

    uint64_t newobjid = simidx.Reserve();
    retval = factory_createfromtemplate(tid, templ, newobjid);
    if (retval != 0) {
        retval->parent = parent;
        retval->objid  = INVALID_OBJID;
        simidx.Add(retval);
        if (doInit) {
            //
            //  As the object always has the update function set to init.
            //  We only need to call init andeverything is fine.
            if (retval->update != nullptr) {
                retval->update(retval, 0ul);
            }
        }
    } else {
        simidx.Release(newobjid);
    }
 
     return retval;
 }
 
tSimObj* NewObject(uint64_t tid, tSimObj *parent, bool doInit) {
    tSimObj* retval = 0;
 
    uint64_t newobjid = simidx.Reserve();
    retval = factory_createnewobj(tid, newobjid);
    if (retval != 0) {
        retval->parent = parent;
        simidx.Add(retval);
        if (doInit) {
            //
            //  As the object always has the update function set to init.
            //  We only need to call init andeverything is fine.
            if (retval->update != nullptr) {
                retval->update(retval, 0ul);
            }
        }
    } else {
        simidx.Release(newobjid);
    }
 
     return retval;
}
