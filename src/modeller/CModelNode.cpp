// *************************************************************************************************************
//
//  Modul-Name     : CModelNode.cpp
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#include <vector>
#include <variant.h>
#include <map>
#include <string>
#include "CModelNode.h"
// Optional
bool CModelNode::isEmpty(void) {
    bool retval = true;
// User-Defined-Code:AAAAAAFw3VF/1PSEIjM=
    if ((!mProperty.empty()) || (!mSubNode.empty())) {
        retval = false;
    }
// End-Of-UDC:AAAAAAFw3VF/1PSEIjM=
    return  (retval);
}

