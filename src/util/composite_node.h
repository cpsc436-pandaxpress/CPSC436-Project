//
// Created by Kenneth William on 2019-02-24.
//

#ifndef PANDAEXPRESS_COMPOSITE_NODE_H
#define PANDAEXPRESS_COMPOSITE_NODE_H

#include "node.h"
#include "vector"

class CompositeNode : public Node {  //  This type of Node follows the Composite Pattern, containing a list of other Nodes.
private:
    std::vector<Node*> children;
public:
    std::vector<Node*> getChildren();
    void addChild (Node* child);
};

#endif //PANDAEXPRESS_COMPOSITE_NODE_H
