//
// Created by Prayansh Srivastava on 2019-03-27.
//

#ifndef PANDAEXPRESS_HUD_TRANSFORM_SYSTEM_H
#define PANDAEXPRESS_HUD_TRANSFORM_SYSTEM_H


#include "system.h"

class HudTransformSystem : public System {
private:
public:
    HudTransformSystem();

    void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;
};


#endif //PANDAEXPRESS_HUD_TRANSFORM_SYSTEM_H
