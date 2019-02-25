//
// Created by Kenneth William on 2019-02-23.
//

#ifndef PANDAEXPRESS_CHASES_H
#define PANDAEXPRESS_CHASES_H

/***
 * This component gives the entity the ability to chase whatever entity is passed in as it's target
 * Right now this is done with a simple check on the targets position, but A* will be implemented in
 * the chases_system later
 */
struct Chases {
    uint32_t target;

    explicit Chases(uint32_t target) :
            target(target)
    {}
};
#endif //PANDAEXPRESS_CHASES_H
