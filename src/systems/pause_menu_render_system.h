//
// Created by Avery Brown on 2019-03-31.
//

#ifndef PANDAEXPRESS_PAUSE_MENU_RENDER_SYSTEM_H
#define PANDAEXPRESS_PAUSE_MENU_RENDER_SYSTEM_H

#include "system.h"

class PauseMenuRenderSystem : public System {
public:
    PauseMenuRenderSystem();

    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;

};
#endif //PANDAEXPRESS_PAUSE_MENU_RENDER_SYSTEM_H
