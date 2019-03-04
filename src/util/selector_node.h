//
// Created by Kenneth William on 2019-02-24.
//

#ifndef PANDAEXPRESS_SELECTOR_NODE_H
#define PANDAEXPRESS_SELECTOR_NODE_H

#include "node.h"
#include "vector"


class SelectorNode : public Node {
private:
    std::vector<Node*> children;
public:
    virtual bool run() override;
    std::vector<Node*> getChildren();
    void addChild (Node* child);
    SelectorNode();
};



#endif //PANDAEXPRESS_SELECTOR_NODE_H
