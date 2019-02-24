//
// Created by Rebecca Roth on 2019-02-22.
//

#ifndef PANDAEXPRESS_GHOST_H
#define PANDAEXPRESS_GHOST_H

#include "util/gl_utils.h"

struct Ghost {

    // points and tangents for swoop curve
    vec2 start_pt;
    vec2 aim_pt;
    vec2 start_tangent;
    vec2 aim_tangent;

    float waittime;
    float swoopTime;

    bool onScreen;
    bool waiting;
    bool waiting_high;
    bool waiting_low;
    bool waiting_right;
    bool waiting_left;

    Ghost() : waittime(10.0), swoopTime(0.0), start_pt({0.0,0.0}), start_tangent({0.0,0.0}),
              aim_pt({0.0,0.0}), aim_tangent({0.0,0.0}), onScreen(false), waiting(false),
              waiting_high(true), waiting_low(false), waiting_right(false), waiting_left(true){}
};
#endif //PANDAEXPRESS_GHOST_H
