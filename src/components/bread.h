//
// Created by Rebecca on 2019-02-02.
//

#ifndef PANDAEXPRESS_BREAD_H
#define PANDAEXPRESS_BREAD_H

struct Bread {
    float width, height;
    bool alive;
    float x_velocity, y_velocity;

    Bread(float width, float height) :
            width(width),
            height(height),
            alive(true),
            x_velocity(-50.f),
            y_velocity(0) {}
};

#endif //PANDAEXPRESS_BREAD_H
