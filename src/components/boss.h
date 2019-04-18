//
// Created by Kenneth William on 2019-04-14.
//

#ifndef PANDAEXPRESS_BOSS_H
#define PANDAEXPRESS_BOSS_H
struct Boss {
    bool alive;
    bool evading;
    int invincibility_timer;


    Boss() : alive(true),
                invincibility_timer(0){}
};
#endif //PANDAEXPRESS_BOSS_H
