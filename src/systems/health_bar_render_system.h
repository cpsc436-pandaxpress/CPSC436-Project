//
// Created by Prayansh Srivastava on 2019-03-07.
//

#ifndef PANDAEXPRESS_HEALTH_BAR_RENDER_SYSTEM_H
#define PANDAEXPRESS_HEALTH_BAR_RENDER_SYSTEM_H

#include "system.h"

class HealthBarRenderSystem : public System {
public:
    HealthBarRenderSystem();

    virtual void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;
};

#endif //PANDAEXPRESS_HEALTH_BAR_RENDER_SYSTEM_H
