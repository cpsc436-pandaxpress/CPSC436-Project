//
// Created by Prayansh Srivastava on 2019-02-06.
//

#include <graphics/background.h>
#include "background_render_system.h"

BackgroundRenderSystem::BackgroundRenderSystem() {

}

void BackgroundRenderSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    auto viewBg = registry.view<Background>();
    Camera &camera = blackboard.camera;
    for (auto entity: viewBg) {
        //get the sprite
        auto& background = viewBg.get(entity);

        //draw to the window
        blackboard.window.draw((Renderable*)(&background), blackboard.camera.get_projection());
    }
}
