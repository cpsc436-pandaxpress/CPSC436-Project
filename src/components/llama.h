//
// Created by Rebecca Roth on 2019-02-22.
//

#ifndef PANDAEXPRESS_LLAMA_H
#define PANDAEXPRESS_LLAMA_H

struct Llama {
    bool alive;
    int spit_time;

    Llama() : alive(true), spit_time(500) {}
};

#endif //PANDAEXPRESS_LLAMA_H
