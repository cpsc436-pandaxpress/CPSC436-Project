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
    bool falling;
    bool shakeLeft;
    bool shaking;
    bool trigger;

    Platform(bool one_way = true, bool falling = false) : one_way(one_way),falling(falling), shakeLeft(false),shaking(false),trigger(false) {}

};
#endif //PANDAEXPRESS_PLATFORM_H
