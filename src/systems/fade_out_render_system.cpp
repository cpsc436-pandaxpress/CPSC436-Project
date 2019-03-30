//
// Created by Avery Brown on 2019-03-29.
//

#include "fade_out_render_system.h"
#include <graphics/fade.h>

FadeOutRenderSystem::FadeOutRenderSystem() {}

void FadeOutRenderSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    // construct a view for all entities with a sprite
//    auto view = registry.view<Fade>();
//
//    for (auto entity: view) {
//        //get the sprite
//        auto& cave = view.get(entity);
//
//        //draw to the window
//        blackboard.window.draw((Renderable*)(&cave), blackboard.camera.get_projection());
//    }
}