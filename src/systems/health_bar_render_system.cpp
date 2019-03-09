//
// Created by Prayansh Srivastava on 2019-03-07.
//

#include <graphics/health_bar.h>
#include "health_bar_render_system.h"

HealthBarRenderSystem::HealthBarRenderSystem() {}

void HealthBarRenderSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    // construct a view for all entities with a sprite
    auto view = registry.view<HealthBar>();

    for (auto entity: view) {
        //get the sprite
        auto& healthBar = view.get(entity);

        //draw to the window
        blackboard.window.draw((Renderable*)(&healthBar), blackboard.camera.get_projection());
    }
}