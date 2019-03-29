//
// Created by Kenneth William on 2019-03-29.
//

#ifndef PANDAEXPRESS_SEEKS_H
#define PANDAEXPRESS_SEEKS_H

#include <vector>
#include "util/coordinates.h"

/***
 * This component gives the entity the ability to chase whatever entity is passed in as it's target
 * Right now this is done with a simple check on the targets position, but A* will be implemented in
 * the chases_system later
 */
struct Seeks {
    std::vector<Coordinates*> seekList;
    float seek_speed;
    bool alive;

    explicit Seeks(std::vector<Coordinates*> seeklist) :
            seekList(seeklist),
            seek_speed(120.f),
            alive(true)

    {}
};


#endif //PANDAEXPRESS_SEEKS_H
