//
// Created by Prayansh Srivastava on 2019-03-03.
//

#include <graphics/text.h>
#include "text_render_system.h"

TextRenderSystem::TextRenderSystem() {

}

void TextRenderSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    // construct a view for all entities with a sprite
    auto view = registry.view<Text>();

    for (auto entity: view) {
        //get the sprite
        auto& text = view.get(entity);

        //draw to the window
        blackboard.window.draw((Renderable*)(&text), blackboard.camera.get_projection());
    }
}
