// *************************************************************************************************************
//
//  Modul-Name     : generated.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef __GENERATED_INC__
#define __GENERATED_INC__

#include <stdint.h>
#include <simobj.h>
#include <pointerindex.h>
#include <logger.h>

extern CPointerIndex simidx;
extern CLogger       simlog;

//
//
tSimObj* NewObjectFromTemplate(uint64_t tid, uint64_t templ, tSimObj* parent = 0, bool doInit = true);
//
//  This creates a new object of the given type and returns the pointer
//  to it. The object gets initialized according to the model.
tSimObj* NewObject(uint64_t tid, tSimObj* parent = 0, bool doInit = true);

#endif // __GENERATED_INC__
