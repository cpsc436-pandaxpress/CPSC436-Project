//
// Created by Kenneth William on 2019-02-02.
//

#ifndef PANDAEXPRESS_WALKABLE_H
#define PANDAEXPRESS_WALKABLE_H

/***
 * Component that determines whether or not an entity can interact with the environment.
 * If assigned this component the entity can walk on platforms, not walk through walls, bounce on spring etc
 * An object without this component can still be collidable or cause damage to the player(eg Bullet Bill
 *  in Mario goes through walls but can still damage the player)
 ***/
struct Interactable {
    bool grounded;  // Represents whether the entity is standing on the ground

    Interactable() :
            grounded(false) {}

};

#endif //PANDAEXPRESS_WALKABLE_H
