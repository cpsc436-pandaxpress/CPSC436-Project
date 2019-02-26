//
// Created by Kenneth William on 2019-02-03.
//

#ifndef PANDAEXPRESS_FOOD_H
#define PANDAEXPRESS_FOOD_H

/***
 * This component tags an entity as being something that interactable entities can walk on
 */
struct Food {
    bool eaten;

    Food() : eaten(false) {}
};
#endif //PANDAEXPRESS_FOOD_H
