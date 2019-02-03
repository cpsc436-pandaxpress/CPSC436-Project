//
// Created by Kenneth William on 2019-02-02.
//

#ifndef PANDAEXPRESS_VELOCITY_H
#define PANDAEXPRESS_VELOCITY_H

/***
 * This component should be assigned to anything that will be given a velocity
 * Without this component the object will remain in place even if camera moves
 */
struct Velocity {
    float x_velocity, y_velocity;

    Velocity(float x_velocity, float y_velocity) :
            x_velocity(0.f),
            y_velocity(0.f){}
};

#endif //PANDAEXPRESS_VELOCITY_H
