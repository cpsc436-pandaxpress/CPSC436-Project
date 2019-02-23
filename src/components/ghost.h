//
// Created by Rebecca Roth on 2019-02-22.
//

#ifndef PANDAEXPRESS_GHOST_H
#define PANDAEXPRESS_GHOST_H

struct Ghost {

    int waittime;
    int offScreenTime;
    bool onScreen;
    bool waiting;
    bool waiting_high;
    bool waiting_low;
    bool waiting_right;
    bool waiting_left;

    Ghost() : waittime(200), offScreenTime(700), onScreen(false), waiting(false), waiting_high(true),
    waiting_low(false), waiting_right(false), waiting_left(true){}
};
#endif //PANDAEXPRESS_GHOST_H
