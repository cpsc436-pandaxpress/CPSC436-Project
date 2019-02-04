//
// Created by Kenneth William on 2019-01-31.
//

#ifndef PANDAEXPRESS_COLLIDABLE_H
#define PANDAEXPRESS_COLLIDABLE_H

/***
 * This component specifies that the entity can be checked for collisions with other entities
 * The width and height will be used for creating the bounding box
 */

struct Collidable {
    float width, height;

    Collidable(float width, float height) :
            width(width), height(height) {}
};

#endif //PANDAEXPRESS_COLLIDABLE_H
