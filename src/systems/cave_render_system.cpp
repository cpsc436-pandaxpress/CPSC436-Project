//
// Created by Becca Roth on 2019-03-08.
//

#include "cave_render_system.h"
#include <graphics/cave.h>
#include <graphics/cave_entrance.h>

CaveRenderSystem::CaveRenderSystem() {}

void CaveRenderSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    // construct a view for all entities with a sprite
    auto view = registry.view<Cave>();

    for (auto entity: view) {
        //get the sprite
        auto& cave = view.get(entity);

        //draw to the window
        blackboard.window.draw((Renderable*)(&cave), blackboard.camera.get_projection());
    }
    auto view_entrance = registry.view<CaveEntrance>();

    for (auto entity: view_entrance) {
        auto& cave_entrance = view_entrance.get(entity);

        //draw to the window
        blackboard.window.draw((Renderable*)(&cave_entrance), blackboard.camera.get_projection());
    }
}