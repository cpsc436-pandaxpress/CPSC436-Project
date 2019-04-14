//
// Created by Prayansh Srivastava on 2019-04-07.
//

#ifndef PANDAEXPRESS_RENDER_SYSTEM_H
#define PANDAEXPRESS_RENDER_SYSTEM_H


#include "system.h"

/**
 * Main Render System, compiles a vector of all renderables, then sorts them according to their
 * depth values and renders them
 */
class RenderSystem : public System {
public:
    void update(Blackboard &blackboard, entt::DefaultRegistry &registry);

private:
    void updateLayers(entt::DefaultRegistry &registry);
};


#endif //PANDAEXPRESS_RENDER_SYSTEM_H
