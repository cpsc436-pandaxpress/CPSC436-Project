//
// Created by Becca Roth on 2019-03-08.
//

#ifndef PANDAEXPRESS_CAVE_RENDER_SYSTEM_H
#define PANDAEXPRESS_CAVE_RENDER_SYSTEM_H

#include "system.h"

class CaveRenderSystem : public System {
public:
    CaveRenderSystem();

    virtual void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;
};


#endif //PANDAEXPRESS_CAVE_RENDER_SYSTEM_H
