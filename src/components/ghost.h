//
// Created by Rebecca Roth on 2019-02-22.
//

#ifndef PANDAEXPRESS_GHOST_H
#define PANDAEXPRESS_GHOST_H

struct Ghost {

    int waittime;
    int offScreenTime;
    float swoopTime;
    float start_x;
    float start_y;
    float aim_x;
    float aim_y;
    float start_tangent ;
    float aim_tangent;
    bool onScreen;
    bool waiting;
    bool waiting_high;
    bool waiting_low;
    bool waiting_right;
    bool waiting_left;

    Ghost() : waittime(200), offScreenTime(700), swoopTime(0.0), start_x(0.0), start_y(0.0), start_tangent(1),
              aim_x(0.0), aim_y(0.0), aim_tangent(0), onScreen(false), waiting(false), waiting_high(true),
              waiting_low(false), waiting_right(false), waiting_left(true){}
};
#endif //PANDAEXPRESS_GHOST_H
