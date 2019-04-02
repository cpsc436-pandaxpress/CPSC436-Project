//
// Created by Rebecca on 2019-02-02.
//

#ifndef PANDAEXPRESS_DRACULA_H
#define PANDAEXPRESS_DRACULA_H

struct Dracula {
    bool alive;
    bool evading;
    int invincibility_timer;

    Dracula() : alive(true),
    invincibility_timer(0){}
};

#endif //PANDAEXPRESS_DRACULA_H
