//
// Created by Kenneth William on 2019-02-02.
//

#ifndef PANDAEXPRESS_HEALTH_H
#define PANDAEXPRESS_HEALTH_H

/***
 * Adding this component to an entity will allow it to take damage when it's hit by another entity
 * that has been assigned the causesDamage component.  Once the healthPoints become zero the entity
 * should be considered dead
 */

struct Health {
    int health_points;
    int max_health;


    Health(int healthPoints) :
            Health(healthPoints, healthPoints) {}

    Health(int healthPoints, int maxPoints) :
            health_points(healthPoints),
            max_health(maxPoints) {}
};
#endif //PANDAEXPRESS_HEALTH_H
