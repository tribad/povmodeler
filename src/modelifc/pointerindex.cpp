#include "pointerindex.h"
#include "ptrnode.h"

std::map<uint64_t, CPtrNode*> CPointerIndex::Root;

CPointerIndex::CPointerIndex()
{

}

void CPointerIndex::Add(tSimObj *obj, uint64_t vers) {
    //
    //  If we do not have a root element for this version we create one.
    if (Root[vers] == 0) {
        Root[vers] = new CPtrNode();
    }
    if (obj->objid == INVALID_OBJID) {
        Root[vers] = Root[vers]->Allocate(obj->objid);
    }
    //
    //  The root maybe moved if new layers gets added.
    Root[vers] = Root[vers]->Insert(obj->objid, obj);
}

void CPointerIndex::Delete(tSimObj *obj, uint64_t vers) {
    //
    //  If we do not have a root element for this version we
    //  assume it is already deleted.
    if (Root[vers] != 0) {
        Root[vers]->Remove(obj->objid);
    }
}

uint64_t CPointerIndex::Reserve(uint64_t id, uint64_t vers) {
    //
    //  If we do not have a root element for this version we create one.
    if (Root[vers] == 0) {
        Root[vers] = new CPtrNode();
    }
    if (id == INVALID_OBJID) {
        Root[vers] = Root[vers]->Allocate(id);
    }
    if (id != INVALID_OBJID) {
        //
        //  The root maybe moved if new layers gets added.
        Root[vers] = Root[vers]->Insert(id, 0);
    }
    return id;
}

bool CPointerIndex::Release(uint64_t id, uint64_t vers) {
    bool retval = true;
    //
    //  If we do not have a root element for this version we
    //  think its released. ;)
    if (Root[vers] != 0) {
        retval = Root[vers]->Release(id);
    }

    return retval;
}

tSimObj* CPointerIndex::Find(uint64_t id, uint64_t vers) {
    tSimObj* retval = 0;
    //
    //  If we do not have a root element we return 0
    if (Root[vers] != 0) {
        retval = (tSimObj*)(Root[vers]->Find(id));
    }

    return retval;
}
