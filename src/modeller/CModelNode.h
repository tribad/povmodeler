// *************************************************************************************************************
//
//  Modul-Name     : CModelNode.h
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
#pragma once
#ifndef CMODELNODE_INC
#define CMODELNODE_INC
//
//  This is the class
class CModelNode {
public:
    CModelNode() = default;
    ~CModelNode() = default;
    bool isEmpty(void) ;
private:
    std::vector<CModelNode*>        mSubNode;
    CModelNode*                     mParent;
    std::map<std::string, tVariant> mProperty;
};

#endif  // CMODELNODE_INC
