//
// Created by Kenneth William on 2019-02-23.
//

#ifndef PANDAEXPRESS_CHASES_H
#define PANDAEXPRESS_CHASES_H
struct Chases {
    uint32_t target;

    explicit Chases(uint32_t target) :
            target(target)
    {}
};
#endif //PANDAEXPRESS_CHASES_H
