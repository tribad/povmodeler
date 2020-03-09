/*
 * simobj.h
 *
 *  Created on: Jun 13, 2014
 *      Author: ltoo
 */
#ifndef SIMOBJ_H_
#define SIMOBJ_H_
/*
 * Additional headerfiles needed everywhere
 */
#include <map>
#include <stdint.h>
#include <string.h>
#include <variant.h>
#include <msg.h>
#ifdef __USE_GROBJECT
    #include <grobject.h>
    #include <grstream.h>
#endif

#define INVALID_OBJID UINT64_MAX

/*
 * Forward declaration of the object base structure.
 */
struct tSimObj;
/*
 * Definitions of types that describe the function
 * of the type.
 */
typedef uint64_t typeid_t;
typedef uint64_t valueid_t;
typedef uint64_t objectid_t;
typedef uint64_t valueindex_t;
typedef uint64_t templateid_t;
/*
 * Definition of some pointer to function types.
 * They are used to be handled in the simulation.
 */
typedef int       (*tSetValue)(tSimObj*, valueid_t valueid, valueindex_t valueindex, const tVariant& value);
typedef tVariant  (*tGetValue)(tSimObj*, valueid_t valueid, valueindex_t valueindex);
typedef int       (*tSave)(tSimObj*, uint64_t cycle, ...);
typedef void      (*tUpdate)(tSimObj *, uint64_t);
typedef void      (*tProcess)(tSimObj*, tMsg*);
typedef tMsg*     (*tSyncProcess)(tSimObj*, tMsg*);
/*
 * This is the basic simulation object structure
 */
struct tSimObj {
    objectid_t       objid;       /* This is a unique identifier of an object.                      */
    typeid_t         type;        /* This is a unique identifier of the object-type                 */
    tSimObj          *parent;     /* This is the pointer to the parent. Maybe useless               */
    tSetValue        setvalue;    /* A pointer to a function that can set a value in the object     */
    tGetValue        getvalue;    /* A pointer to a function that can get a value of the object     */
    tSave            save;        /* A pointer to a function that can save the object state         */
    tUpdate          update;      /* A pointer to an update function.                               */
    tProcess         process;     /* A pointer to an message processing function                    */
    tSyncProcess     syncprocess; /* A pointer to a synchronuos message processing function         */
#if (SIMVERSION != 2)
    uint64_t         state;       /* The state of the object                                        */
#endif
#ifdef __USE_GROBJECT
    CGrObject*       graphic;     /* Pointer to a graphical representation of the simulation object */
#endif
};
/*
 * This is a reference to another object.
 * Because we have to different versions of references
 * pointers while loaded and objid's while stored we use both here.
 * We do not know when we can change from one to the other.
 * So we do not use a union but a struct.
 */
using tSimObjRef     = tObjectRef;
using tSimObjRefIter = std::map<uint64_t, tSimObjRef>::iterator;

#endif /* SIMOBJ_H_ */
