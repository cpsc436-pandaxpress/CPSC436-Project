//
// Created by Kenneth William on 2019-02-02.
//

#ifndef PANDAEXPRESS_VELOCITY_H
#define PANDAEXPRESS_VELOCITY_H

/***
 * This component should be assigned to anything that will be given a velocity
 * Without this component the object will remain in place even if camera moves
 *
 * In the future maybe this can be combined with momentum and other physical forces but this
 * should be fine for the skeletal game
 */
struct Velocity {
    float x_velocity, y_velocity;

    Velocity() : Velocity(0.f, 0.f) {}

    Velocity(float x_velocity, float y_velocity) :
            x_velocity(x_velocity),
            y_velocity(y_velocity){}
};

#endif //PANDAEXPRESS_VELOCITY_H
