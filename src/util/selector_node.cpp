//
// Created by Kenneth William on 2019-02-24.
//
#include "selector_node.h"

SelectorNode::SelectorNode(){}

 bool SelectorNode::run()  {
    for (Node* child : getChildren()) {  // The generic Selector implementation
        if (child->run() == true)  // If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.
            return true;
    }
    return false;  // All children failed so the entire run() operation fails.
}