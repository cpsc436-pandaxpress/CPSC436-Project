//
// Created by Rebecca on 2019-02-02.
//

#ifndef PANDAEXPRESS_JACKO_H
#define PANDAEXPRESS_JACKO_H

struct Jacko {
    bool alive;
    bool evading;
    int invincibility_timer;

    Jacko() : alive(true),
    evading(false),
    invincibility_timer(0) {}
};

#endif //PANDAEXPRESS_BREAD_H
