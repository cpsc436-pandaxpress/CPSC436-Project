//
// Created by Prayansh Srivastava on 2019-03-07.
//

#ifndef PANDAEXPRESS_HEALTH_BAR_TRANSFORM_SYSTEM_H
#define PANDAEXPRESS_HEALTH_BAR_TRANSFORM_SYSTEM_H

#include "system.h"

class HealthBarTransformSystem : public System {
public:
    HealthBarTransformSystem();

    virtual void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;
};


#endif //PANDAEXPRESS_HEALTH_BAR_TRANSFORM_SYSTEM_H
