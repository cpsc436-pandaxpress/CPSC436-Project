//
// Created by alex on 27/01/19.
//

#include "sprite_render_system.h"

#include "../graphics/sprite.h"

SpriteRenderSystem::SpriteRenderSystem() {

}

void SpriteRenderSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    // construct a view for all entities with a sprite
    auto view = registry.view<Sprite>();

    for (auto entity: view) {
        //get the sprite
        auto& sprite = view.get(entity);

        //draw to the window
        blackboard.window.draw((Renderable*)(&sprite), blackboard.camera.get_projection());
    }
}