//
// Created by Kenneth William on 2019-02-24.
//
#include "selector_node.h"


SelectorNode::SelectorNode(){}

/***
 * If any of the children return true the whole node returns true
 * Idea for implementation from http://www.cplusplus.com/forum/general/141582/
 */
 bool SelectorNode::run()  {
    for (Node* child : getChildren()) {
        if (child->run())
            return true;
    }
    return false;
}

std::vector<Node*> SelectorNode::getChildren(){
    return children;
}
void SelectorNode::addChild (Node* child){
    children.push_back(child);
}