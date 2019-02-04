//
// Created by cowan on 30/01/19.
//

#ifndef PANDAEXPRESS_PHYSICS_H
#define PANDAEXPRESS_PHYSICS_H

struct Panda {
    float width, height;
    bool alive;

    Panda(float width, float height) :
        width(width),
        height(height),
        alive(true)
        {}
};

#endif //PANDAEXPRESS_PHYSICS_H