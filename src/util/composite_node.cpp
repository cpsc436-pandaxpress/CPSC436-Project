//
// Created by Kenneth William on 2019-02-24.
//
#include "composite_node.h"


std::vector<Node*> CompositeNode::getChildren(){
    return children;
}
void CompositeNode::addChild (Node* child){
    children.push_back(child);
}