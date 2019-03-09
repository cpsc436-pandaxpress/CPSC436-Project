//
// Created by Rebecca on 2019-02-02.
//

#ifndef PANDAEXPRESS_BREAD_H
#define PANDAEXPRESS_BREAD_H

struct Bread {
    bool alive;
    bool started;
    bool left;

    Bread() : Bread(true) {}

    Bread(bool move_left) : alive(true), started(false), left(move_left) {}
};

#endif //PANDAEXPRESS_BREAD_H