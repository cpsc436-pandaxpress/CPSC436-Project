//
// Created by Avery Brown on 2019-03-30.
//

#include <components/panda.h>
#include <components/tutorial.h>
#include <components/transform.h>
#include <components/health.h>
#include <components/timer.h>
#include <components/velocity.h>
#include <components/interactable.h>
#include "pause_system.h"

PauseSystem::PauseSystem() {

}

void PauseSystem::update(Blackboard& blackboard, entt::DefaultRegistry& registry) {
    float scaleY = 0.25;
    float scaleX = 0.25;
//    auto &tutorial_trans = registry.get<Transform>(tutorial2_entity);
//
//    if (tutorial_trans.x + 100.f < blackboard.camera.position().x - blackboard.camera.size().x / 2.0 ){
//        auto &tutorial_trans = registry.replace<Transform>(tutorialentity, -1500.f, -200.f, 0.f, scaleX, scaleY);
//        auto &tutorial2_trans = registry.replace<Transform>(tutorial2entity, -1500.f,  -200.f, 0.f, scaleX, scaleY);
//    }
}

//void HorizontalScene::create_tutorial(Blackboard &blackboard) {
//    tutorial_entity = registry_.create();
//    tutorial2_entity = registry_.create();
//
//    auto texture = blackboard.texture_manager.get_texture("tutorial");
//    auto texture2 = blackboard.texture_manager.get_texture("tutorial_bread");
//
//    auto shader = blackboard.shader_manager.get_shader("sprite");
//    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
//
//    float scaleY = 0.25;
//    float scaleX = 0.25;
//    registry_.assign<Sprite>(tutorial_entity, texture, shader, mesh);
//    registry_.assign<Tutorial>(tutorial_entity);
//    registry_.assign<Transform>(tutorial_entity, 400.f, -200.f, 0., scaleX, scaleY);
//
//    registry_.assign<Sprite>(tutorial2_entity, texture2, shader, mesh);
//    registry_.assign<Tutorial>(tutorial2_entity);
//    registry_.assign<Transform>(tutorial2_entity, 900.f, -200.f, 0., scaleX, scaleY);
//
//}