//
// Created by cowan on 30/01/19.
//

#ifndef PANDAEXPRESS_PHYSICS_H
#define PANDAEXPRESS_PHYSICS_H

struct Panda {
    float width, height;
    bool grounded;
    float x_velocity, y_velocity;

    Panda(float width, float height) :
        width(width),
        height(height),
        grounded(false),
        x_velocity(0),
        y_velocity(0) {}
};

#endif //PANDAEXPRESS_PHYSICS_H