//
// Created by alex on 27/01/19.
//

#include "sprite_render_system.h"

#include "../graphics/sprite.h"
#include "../components/layer.h"

SpriteRenderSystem::SpriteRenderSystem() {

}

void SpriteRenderSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    // Sort Layer components by their layer property
    registry.sort<Layer, CompareLayer>(CompareLayer());

    // Sort Sprite components according to how Layer components are sorted
    // Sprites who's entities have no Layer component will be placed after the others
    registry.sort<Sprite, Layer>();

    auto view = registry.view<Sprite>();

    for (auto entity: view) {
        //get the sprite
        auto& sprite = view.get(entity);

        //draw to the window
        blackboard.window.draw((Renderable*)(&sprite), blackboard.camera.get_projection());
    }
}
