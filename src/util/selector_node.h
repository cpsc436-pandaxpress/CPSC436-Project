//
// Created by Kenneth William on 2019-02-24.
//

#ifndef PANDAEXPRESS_SELECTOR_NODE_H
#define PANDAEXPRESS_SELECTOR_NODE_H

#include "composite_node.h"
#include "vector"

class SelectorNode : public CompositeNode {
public:
    virtual bool run() override;
    SelectorNode();
};

#endif //PANDAEXPRESS_SELECTOR_NODE_H
