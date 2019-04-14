//
// Created by Kenneth William on 2019-02-24.
//

#ifndef PANDAEXPRESS_NODE_H
#define PANDAEXPRESS_NODE_H

/***
 *   Basically an interface for the nodes of the behaviour tree
 */


class Node {
    public:
        virtual bool run();
        virtual ~Node() = default;

};


#endif //PANDAEXPRESS_NODE_H
