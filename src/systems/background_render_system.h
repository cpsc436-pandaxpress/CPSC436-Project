//
// Created by Prayansh Srivastava on 2019-02-06.
//

#ifndef PANDAEXPRESS_BACKGROUND_RENDER_SYSTEM_H
#define PANDAEXPRESS_BACKGROUND_RENDER_SYSTEM_H


#include "system.h"

class BackgroundRenderSystem : public System {
public:
    BackgroundRenderSystem();

    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;

};


#endif //PANDAEXPRESS_BACKGROUND_RENDER_SYSTEM_H
