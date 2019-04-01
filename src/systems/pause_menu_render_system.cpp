//
// Created by Avery Brown on 2019-03-31.
//

#include "pause_menu_render_system.h"

#include "../graphics/sprite.h"
#include "components/pause_menu.h"

PauseMenuRenderSystem::PauseMenuRenderSystem() {

}

void PauseMenuRenderSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    // Sort Layer components by their layer property
//    registry.sort<Layer, CompareLayer>(CompareLayer());

    // Sort Sprite components according to how Layer components are sorted
    // Sprites who's entities have no Layer component will be placed after the others
//    registry.sort<Sprite, PauseMenu>();

    auto view = registry.view<Sprite, PauseMenu>();

    for (auto entity: view) {
        //get the sprite
        auto& sprite = view.get<Sprite>(entity);
        auto& pauseMenu = view.get<PauseMenu>(entity);

        //draw to the window
        blackboard.window.draw((Renderable*)(&sprite), blackboard.camera.get_projection());
    }
}