//
// Created by Kenneth William on 2019-01-31.
//

#ifndef PANDAEXPRESS_COLLIDABLE_H
#define PANDAEXPRESS_COLLIDABLE_H


struct Collidable {
    float width, height;
    bool hurtsPanda;

    Collidable(float width, float height, bool hurtsPanda) :
            width(width), height(height), hurtsPanda(hurtsPanda) {}
};

#endif //PANDAEXPRESS_COLLIDABLE_H
