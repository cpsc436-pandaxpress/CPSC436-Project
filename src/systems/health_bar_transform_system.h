//
// Created by Prayansh Srivastava on 2019-03-07.
//

#ifndef PANDAEXPRESS_HEALTH_BAR_TRANSFORM_SYSTEM_H
#define PANDAEXPRESS_HEALTH_BAR_TRANSFORM_SYSTEM_H

#include "system.h"

class HealthBarTransformSystem : public System {
private:
    const float PANDA_HB_OFFSET_X = 100.f;
    const float PANDA_HB_OFFSET_Y = 50.f;
public:
    HealthBarTransformSystem();

    virtual void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;
};


#endif //PANDAEXPRESS_HEALTH_BAR_TRANSFORM_SYSTEM_H
