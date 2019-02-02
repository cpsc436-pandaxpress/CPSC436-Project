//
// Created by Rebecca on 2019-02-02.
//

#ifndef PANDAEXPRESS_BREAD_H
#define PANDAEXPRESS_BREAD_H

struct Bread {
    float width, height;
    bool grounded;
    float x_velocity, y_velocity;

    Bread(float width, float height) :
            width(width),
            height(height),
            grounded(false),
            x_velocity(-0.5f),
            y_velocity(0) {}
};

#endif //PANDAEXPRESS_BREAD_H
