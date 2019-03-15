//
// Created by cowan on 30/01/19.
//

#ifndef PANDAEXPRESS_PHYSICS_H
#define PANDAEXPRESS_PHYSICS_H

/***
 * The entity assigned the Panda component is able to be controlled by the player_movement_system
 *
 */

struct Panda {
    bool alive;
    bool invincible, recovering, facingRight;

    Panda() :
        alive(true),
        invincible(false),
        recovering(false),
        facingRight(true)
        {}
};

#endif //PANDAEXPRESS_PHYSICS_H