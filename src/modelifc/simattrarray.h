#ifndef SIMATTRARRAY_H
#define SIMATTRARRAY_H

#include <map>
#include <simattribute.h>

typedef std::map<uint64_t, CSimAttribute>::iterator tSimAttrArrayIter;

class CSimAttrArray : public CSimAttrBase
{
public:
    CSimAttrArray(uint64_t aOID, uint64_t aVID, eSimAttrType aType, bool aShared=false);
    CSimAttrArray(bool aShared=false);
    CSimAttribute& operator[](uint64_t aIndex);
    size_t size() {return array.size();}
    tSimAttrArrayIter begin() {return array.begin();}
    tSimAttrArrayIter end() {return array.end();}
    tSimAttrArrayIter find(uint64_t key) {return array.find(key);}
    void erase(uint64_t key);
private:
    bool                              shared;
    pthread_spinlock_t                array_lock;
    pthread_t                         locking_thread;
    std::map<uint64_t, CSimAttribute> array;
};

#endif // SIMATTRARRAY_H
