//
// Created by Kenneth William on 2019-02-03.
//

#ifndef PANDAEXPRESS_FLOATING_PLATFORM_H
#define PANDAEXPRESS_FLOATING_PLATFORM_H

/***
 * A platform that falls after the player steps on it
 */
struct FallingPlatform {
    bool shaking;
    FallingPlatform():
        shaking(false)
    {}
};
#endif //PANDAEXPRESS_FLOATING_PLATFORM_H
