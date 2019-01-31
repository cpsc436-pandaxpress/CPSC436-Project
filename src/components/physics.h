//
// Created by cowan on 30/01/19.
//

#ifndef PANDAEXPRESS_PHYSICS_H
#define PANDAEXPRESS_PHYSICS_H

struct Physics {
    bool gravity;
    float x_velocity, y_velocity;

    Physics() : gravity(false), x_velocity(0), y_velocity(0) {}
    Physics(float gravity) : gravity(gravity) {}
    Physics(float gravity, float x_velocity, float y_velocity) :
        gravity(gravity), x_velocity(x_velocity), y_velocity(y_velocity) {}
};

#endif //PANDAEXPRESS_PHYSICS_H
