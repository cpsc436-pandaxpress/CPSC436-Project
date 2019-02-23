//
// Created by Rebecca Roth on 2019-02-22.
//

#ifndef PANDAEXPRESS_GHOST_H
#define PANDAEXPRESS_GHOST_H

struct Ghost {

    int waittime;
    bool onScreen;

    Ghost() : waittime(100), onScreen(false) {}
};
#endif //PANDAEXPRESS_GHOST_H
