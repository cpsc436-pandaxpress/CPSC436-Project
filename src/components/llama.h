//
// Created by Rebecca Roth on 2019-02-22.
//

#ifndef PANDAEXPRESS_LLAMA_H
#define PANDAEXPRESS_LLAMA_H

struct Llama {
    bool alive;
    bool left;

    Llama() : Llama(true) {}

    Llama(bool shoots_left) : alive(true), left(shoots_left) {}
};

#endif //PANDAEXPRESS_LLAMA_H
