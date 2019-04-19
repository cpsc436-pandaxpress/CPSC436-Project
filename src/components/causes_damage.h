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

#include <cinttypes>

static constexpr const uint8_t DAMAGE_UP = 1;
static constexpr const uint8_t DAMAGE_DOWN = 2;
static constexpr const uint8_t DAMAGE_LEFT = 4;
static constexpr const uint8_t DAMAGE_RIGHT = 8;

static constexpr const uint8_t PANDA_DMG_MASK = DAMAGE_DOWN;
static constexpr const uint8_t ALL_DMG_MASK = DAMAGE_UP | DAMAGE_DOWN | DAMAGE_LEFT | DAMAGE_RIGHT;
static constexpr const uint8_t TOP_VULNERABLE_MASK = DAMAGE_DOWN | DAMAGE_LEFT | DAMAGE_RIGHT;
static constexpr const uint8_t BOTTOM_VULNERABLE_MASK = DAMAGE_UP | DAMAGE_LEFT | DAMAGE_RIGHT;

struct CausesDamage {
private:
    uint8_t damage_mask;
public:
    int hp;


    CausesDamage(uint8_t damage_mask, int hp) :
        damage_mask(damage_mask),
        hp(hp)
    {}


    // if the normal of the collision with this
    // matches the damage mask
    bool normal_matches_mask(float x_norm, float y_norm) {
        return (x_norm < 0 && damage_mask & DAMAGE_LEFT)
            || (x_norm > 0 && damage_mask & DAMAGE_RIGHT)
            || (y_norm < 0 && damage_mask & DAMAGE_UP)
            || (y_norm > 0 && damage_mask & DAMAGE_DOWN);
    }
};

#endif //PANDAEXPRESS_CAUSESDAMAGE_H
