//
// Created by cowan on 14/04/19.
//

#ifndef PANDAEXPRESS_SHIELD_H
#define PANDAEXPRESS_SHIELD_H

enum PowerupType {
    SHIELD_POWERUP
};

struct Powerup {
    Powerup(PowerupType powerup_type): powerup_type(powerup_type) {}

    PowerupType powerup_type;
};

#endif //PANDAEXPRESS_SHIELD_H
