//
// Created by Kenneth William on 2019-02-02.
//

#ifndef PANDAEXPRESS_CAUSESDAMAGE_H
#define PANDAEXPRESS_CAUSESDAMAGE_H

struct CausesDamage {
    bool xDamage, yDamage;
    int hitPoints;


    CausesDamage(bool xDamage, bool yDamage, int hitPoints) :
            xDamage(xDamage), yDamage(yDamage), hitPoints(hitPoints) {}
};

#endif //PANDAEXPRESS_CAUSESDAMAGE_H