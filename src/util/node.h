//
// Created by Kenneth William on 2019-02-24.
//

#ifndef PANDAEXPRESS_NODE_H
#define PANDAEXPRESS_NODE_H



class Node {  // This class represents each node in the behaviour tree.
    public:
        virtual bool run() = 0;

};


#endif //PANDAEXPRESS_NODE_H
