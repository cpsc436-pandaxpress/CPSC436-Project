//
// Created by Kenneth William on 2019-02-02.
//

#ifndef PANDAEXPRESS_CAUSESDAMAGE_H
#define PANDAEXPRESS_CAUSESDAMAGE_H

/***
 * This component can be applied to an entity to give it the ability to damage entities that
 * have the health component and the collidable component.  xDamage and yDamage are defined separately
 * because some objects will damage the panda if they walk into him, but take damage if he lands on top of them
 */

struct CausesDamage {
    bool xDamage, yDamage;
    int hitPoints;


    CausesDamage(bool xDamage, bool yDamage, int hitPoints) :
            xDamage(xDamage), yDamage(yDamage), hitPoints(hitPoints) {}
};

#endif //PANDAEXPRESS_CAUSESDAMAGE_H
