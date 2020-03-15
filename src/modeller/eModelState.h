// *************************************************************************************************************
//
//  Modul-Name     : eModelState.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef EMODELSTATE_INC
#define EMODELSTATE_INC
//
//                   E n u m e r a t i o n    d e c l a r a t i o n
enum class eModelState {
    Idle,
    Loading,
    Import,
    EmergencySafe
};

#endif  // EMODELSTATE_INC
