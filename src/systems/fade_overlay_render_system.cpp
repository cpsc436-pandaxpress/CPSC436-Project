//
// Created by Avery Brown on 2019-03-29.
//

#include <graphics/fade_overlay.h>
#include "fade_overlay_render_system.h"

FadeOverlayRenderSystem::FadeOverlayRenderSystem() {}

void FadeOverlayRenderSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    // construct a view for all entities with a sprite
    auto view = registry.view<FadeOverlay>();

    for (auto entity: view) {
        //get the sprite
        auto& fadeOverlay = view.get(entity);

        //draw to the window
        blackboard.window.draw((Renderable*)(&fadeOverlay), blackboard.camera.get_projection());
    }
}