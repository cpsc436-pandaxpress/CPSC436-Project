//
// Created by Avery Brown on 2019-03-31.
//

#include <components/pause.h>
#include "pause_menu_render_system.h"

PauseMenuRenderSystem::PauseMenuRenderSystem() {}

void PauseMenuRenderSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    // construct a view for all entities with a sprite
//    auto view = registry.view<Pause>();
//
//    for (auto entity: view) {
//        //get the sprite
//        auto& pauseMenu = view.get(entity);
//
//        //draw to the window
//        blackboard.window.draw((Renderable*)(&pauseMenu), blackboard.camera.get_projection());
//    }
        auto pause_menu = registry.create();

        auto texture = blackboard.texture_manager.get_texture("pause_menu");
        auto shader = blackboard.shader_manager.get_shader("sprite");
        auto mesh = blackboard.mesh_manager.get_mesh("sprite");

        registry.assign<Sprite>(pause_menu, texture, shader, mesh);
        registry.assign<Pause>(pause_menu);
}