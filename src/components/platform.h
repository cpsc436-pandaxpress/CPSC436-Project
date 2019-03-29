//
// Created by Kenneth William on 2019-02-03.
//

#ifndef PANDAEXPRESS_PLATFORM_H
#define PANDAEXPRESS_PLATFORM_H

/***
 * This component tags an entity as being something that interactable entities can walk on
 */
struct Platform {
    bool one_way;

    Platform(bool one_way = true) : one_way(one_way) {}
};
#endif //PANDAEXPRESS_PLATFORM_H
