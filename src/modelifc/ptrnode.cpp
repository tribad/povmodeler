#include "ptrnode.h"
//
//  This method expect to be started on the root-element.
CPtrNode* CPtrNode::Insert(uint64_t id, void *obj) {
    CPtrNode* retval = this;

    uint8_t l;
    //
    //  Find the needed layercount for the id.
    uint8_t* bid = (uint8_t*)(&id);

    for (l=7; l>0; l--) {
        if (bid[l] != 0u) {
            break;
        }
    }
    //
    //  Here we should have the number of needed layers
    //  in l.
    //  If the number of layers needed is larger than we have already
    //  in the tree we add them.
    //  new layers are always on index 0
    while (l > retval->layer) {
        //  Increment the layer id

        uint8_t newlayer = retval->layer + 1;
        //
        //  Create a new layer
        CPtrNode* newup = new CPtrNode;
        //
        //  Setup the layer id for the new layer.
        newup->layer    = newlayer;
        newup->entry[0] = retval;
        //
        //  Link the old root up.
        retval->up      = newup;
        //
        //  Now the the newup layer as to be returned root element.
        retval = newup;
    }
    //
    //  Start insert with
    retval->Insert(bid + retval->layer, obj);
    return retval;
}
//
//  This is a special version starting with the most significant byte
//  that is not zero to insert the id into the tree.
//  We are doing this in a recursive manner because we need to update the usage
//  information on the way out of the tree.
void CPtrNode::Insert(uint8_t *id, void *obj) {
    //
    //  Go through the layers down the tree and create new nodes where needed.
    if (layer != 0) {
        CPtrNode* n;
        //
        //  Need new node here
        if (entry[*id] == 0) {
            entry[*id] = n = new CPtrNode(this);
        } else {
            n = ((CPtrNode*)(entry[*id]));
        }
        n->Insert(id-1, obj);
        //
        //  Check the full flag after insertion.
        //  If the node is full we update the unused map to speedup search for
        //  free ids.
        if (n->full) {
            //
            //  Reset the free bit.
            uint8_t index = (*id) >> 6u;
            uint8_t bit   = (*id) & (0x3f);

            uint64_t mask = ~(1ul << bit);
            unused[index] &= mask;
            //
            //  Check if we have any unused left.
            //  if not set the full flag.
            if (getUnused() == UINT16_MAX) {
                full = true;
            }
        }
    } else {
        //
        //  No we are in the leaf. Insert the obj at position
        entry[*id] = obj;
        //
        //  Reset the free bit.
        uint8_t index = (*id) >> 6u;
        uint8_t bit   = (*id) & (0x3f);

        uint64_t mask = ~(1ul << bit);
        unused[index] &= mask;
        //
        //  Check if we have any unused left.
        //  if not set the full flag.
        if (getUnused() == UINT16_MAX) {
            full = true;
        }
    }
}
//
//  This method expect to be started on the root-element.
void CPtrNode::Remove(uint64_t id) {
    uint8_t l;
    //
    //  Find the needed layercount for the id.
    uint8_t* bid = (uint8_t*)(&id);

    for (l=7; l>0; l--) {
        if (bid[l] != 0u) {
            break;
        }
    }
    //
    //  Here we should have the number of needed layers
    //  in l
    //  If the id expects more layers than are in the tree we
    //  are done yet. The id cannot be in the tree for removal.
    //  Other way round. If the layer in the root is larger or equal
    //  as needed we can proceed.
    if (layer >= l) {
        Remove(bid+layer);
    }
}
//
//  Go down to the leave and remove the object pointer.
//  On the way up update the full maps.
void CPtrNode::Remove(uint8_t *id) {
    if (layer > 0) {
        CPtrNode* r = ((CPtrNode*)(entry[*id]));
        if (r != 0) {
            if (r->full) {
                r->Remove(id-1);
                //
                //  Set the free bit.
                uint8_t index = (*id) >> 6u;
                uint8_t bit   = (*id) & (0x3f);

                uint64_t mask = (1ul << bit);

                unused[index] |= mask;
                full = false;
            } else {
                r->Remove(id-1);
            }
        }
    } else {
        entry[*id] = 0;
        //
        //  Set the free bit.
        uint8_t index = (*id) >> 6u;
        uint8_t bit   = (*id) & (0x3f);

        uint64_t mask = (1ul << bit);

        unused[index] |= mask;
        full = false;
    }
}
//
//  This method expect to be started on the root-element.
bool CPtrNode::Release(uint64_t id) {
    bool retval = true;
    uint8_t l;
    //
    //  Find the needed layercount for the id.
    uint8_t* bid = (uint8_t*)(&id);

    for (l=7; l>0; l--) {
        if (bid[l] != 0u) {
            break;
        }
    }
    //
    //  Here we should have the number of needed layers
    //  in l
    //  If the id expects more layers than are in the tree we
    //  are done yet. The id cannot be in the tree for removal.
    //  Other way round. If the layer in the root is larger or equal
    //  as needed we can proceed.
    if (layer >= l) {
        retval = Release(bid+layer);
    }

    return retval;
}
//
//  Doing the same as with the removal. Going down the tree and release the id.
bool CPtrNode::Release(uint8_t *id) {
    bool retval = true;

    if (layer > 0) {
        CPtrNode* r = ((CPtrNode*)(entry[*id]));
        if (r != 0) {
            if (r->full) {
                retval = r->Release(id-1);
                if (!r->full) {
                    //
                    //  Set the free bit.
                    uint8_t index = (*id) >> 6u;
                    uint8_t bit   = (*id) & (0x3f);

                    uint64_t mask = (1ul << bit);

                    unused[index] |= mask;
                    full = false;
                }
            } else {
                retval = r->Release(id-1);
            }
        }
    } else {
        if (entry[*id] == 0) {
            entry[*id] = 0;
            //
            //  Set the free bit.
            uint8_t index = (*id) >> 6u;
            uint8_t bit   = (*id) & (0x3f);

            uint64_t mask = (1ul << bit);

            unused[index] |= mask;
            full = false;
        } else {
            retval = false;
        }
    }
    return retval;
}
//
//  This method expect to be started on the root-element.
void* CPtrNode::Find(uint64_t id) {
    void*   retval = 0;
    uint8_t l;
    //
    //  Find the needed layercount for the id.
    uint8_t* bid = (uint8_t*)(&id);

    for (l=7; l>0; l--) {
        if (bid[l] != 0u) {
            break;
        }
    }
    //
    //  Here we should have the number of needed layers
    //  in l
    //  If the id expects more layers than are in the tree we
    //  are done yet. The id cannot be in the tree for removal.
    //  Other way round. If the layer in the root is larger or equal
    //  as needed we can proceed.
    if (layer >= l) {
        retval = Find(bid + layer);
    }
    return retval;
}

void* CPtrNode::Find(uint8_t *id) {
    void* retval = 0;

    if (layer > 0) {
        CPtrNode* r = ((CPtrNode*)(entry[*id]));
        if (r != 0) {
            retval = r->Find(id-1);
        }
    } else {
        retval = entry[*id];
    }

    return retval;
}

CPtrNode* CPtrNode::Allocate(uint64_t& id) {
    //
    //  Clear the id so that all bytes are clear.
    id = 0;
    CPtrNode* node = this;
    //
    //  First check if the tree has any free ids.
    //  if not we create a new layer above
    if (full) {
        uint8_t newlayer = layer + 1;
        //
        //  Create a new layer
        node = new CPtrNode;
        //
        //  Setup the layer id for the new layer.
        node->layer    = newlayer;
        //
        //  Add the old root the new node
        node->entry[0] = this;
        //
        //  Remove the free bit
        unused[0] &= (0x01ul);
        //
        //  Link the old root up.
        up      = node;
    }
    node->Allocate(((uint8_t*)(&id)) + node->layer);
    return node;
}
//
//  Going down the tree to create a new id
//  On the way back we setup the usage bits again.
void CPtrNode::Allocate(uint8_t *id) {
    //
    //  The unused map is used here to mark nodes that are free
    //
    uint16_t freeposition = getUnused();

    if (freeposition != UINT16_MAX) {
        //
        //  transfer the free position.
        *id = (uint8_t)(freeposition);
        //
        //  Check if we are on leaf.
        if (layer > 0) {
            //
            //  Check if need to allocate a page down.
            CPtrNode* n;
            if (entry[*id] == 0) {
                entry[*id] = n = new CPtrNode(this);
            } else {
                n = ((CPtrNode*)(entry[*id]));
            }
            //
            //  Anyway we allocated a page down or not we
            //  move on further down.
            n->Allocate(id-1);
            //
            //  Here we are on the way out.
            //  If the page down is full after allocation.
            if (n->full) {
                //
                //  Reset the free bit.
                uint8_t index = (*id) >> 6u;
                uint8_t bit   = (*id) & (0x3f);

                uint64_t mask = ~(1ul << bit);
                unused[index] &= mask;
                //
                //  Check if we have any unused left.
                //  if not set the full flag.
                if (getUnused() == UINT16_MAX) {
                    full = true;
                }
            }
        } else {
            //
            //  Reset the free bit.
            uint8_t index = (*id) >> 6u;
            uint8_t bit   = (*id) & (0x3f);

            uint64_t mask = ~(1ul << bit);
            unused[index] &= mask;
            //
            //  Check if we have any unused left.
            //  if not set the full flag.
            if (getUnused() == UINT16_MAX) {
                full = true;
            }
        }
    }
}
