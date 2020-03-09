#ifndef POINTERINDEX_H
#define POINTERINDEX_H

#include <map>
#include <simobj.h>

class CPtrNode;

class CPointerIndex
{
public:
    CPointerIndex();
    //
    //  Adding an object. If the object has an INVALIDINDEX set as
    //  object id it gets a new index allocated.
    //  In any other case the pointer for the object id gets set/updated.
    void Add(tSimObj* obj, uint64_t vers = 0u);
    //
    //  Removing the Pointer and freeing the index that this objects has
    //  been using.
    void Delete(tSimObj* obj, uint64_t vers = 0u);
    //
    //  Only mark the index as reserved.
    uint64_t Reserve(uint64_t id = INVALID_OBJID, uint64_t vers = 0u);
    //
    //  Release the id and return true if succeeded. If there has been a pointer
    //  allocated to the id, do not release the entry but return false as a result.
    bool Release(uint64_t id, uint64_t vers = 0u);
    //
    //  Find the pointer to the id.
    tSimObj* Find(uint64_t id, uint64_t vers = 0u);
private:
    static std::map<uint64_t, CPtrNode*> Root;
};

#endif // POINTERINDEX_H
