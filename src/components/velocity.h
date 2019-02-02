//
// Created by Kenneth William on 2019-02-02.
//

#ifndef PANDAEXPRESS_VELOCITY_H
#define PANDAEXPRESS_VELOCITY_H

struct Velocity {
    float x_velocity, y_velocity;

    Velocity(float x_velocity, float y_velocity) :
            x_velocity(0.f),
            y_velocity(0.f){}
};

#endif //PANDAEXPRESS_VELOCITY_H
