//
// Created by Prayansh Srivastava on 2019-02-07.
//

#include <graphics/background.h>
#include "background_transform_system.h"

BackgroundTransformSystem::BackgroundTransformSystem() {

}

void BackgroundTransformSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    auto viewBg = registry.view<Background>();
    Camera &camera = blackboard.camera;
    for (auto entity: viewBg) {
        //get the background
        auto &background = viewBg.get(entity);
        // move the background
        float displacement = background.z_pos() * LAYER_SPEED * blackboard.delta_time;
        background.set_pos1(background.pos1().x + displacement, background.pos1().y);
        background.set_pos2(background.pos2().x + displacement, background.pos2().y);
        if (background.pos1().x < (camera.position().x - camera.size().x)) {
            background.set_pos1(background.pos1().x + camera.size().x * 2, background.pos1().y);
        }
        if (background.pos2().x < (camera.position().x - camera.size().x)) {
            background.set_pos2(background.pos2().x + camera.size().x * 2, background.pos2().y);
        }
    }
}
