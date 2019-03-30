//
// Created by Kenneth William on 2019-03-29.
//

#ifndef PANDAEXPRESS_SEEKS_H
#define PANDAEXPRESS_SEEKS_H

#include <vector>
#include "util/coordinates.h"

/***
 * Seeks a series of coordinates
 */
struct Seeks {
    std::vector<Coordinates*> seekList;
    float seek_speed;
    float bounce_speed_x;
    float bounce_speed_y;
    bool goingVertical;
    bool goingHorizontal;

    explicit Seeks(std::vector<Coordinates*> seeklist) :
            seekList(seeklist),
            seek_speed(720.f),
            goingHorizontal(false),
            goingVertical(false),
            bounce_speed_x(360.f),
            bounce_speed_y(360.f)


    {}
};


#endif //PANDAEXPRESS_SEEKS_H
