//
// Created by Prayansh Srivastava on 2019-03-30.
// Code that can be used by multiple systems but doesnt seem to belong to a particular system/scene
//

#ifndef PANDAEXPRESS_SCENE_HELPER_H
#define PANDAEXPRESS_SCENE_HELPER_H


#include <entt/entity/registry.hpp>
#include <graphics/text.h>
#include <components/transform.h>
#include <components/label.h>
#include "blackboard.h"

void generate_label_text(Blackboard &blackboard, entt::DefaultRegistry &registry,
                         vec2 pos, const char *text) {
    auto shader = blackboard.shader_manager.get_shader("text");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    FontType font = blackboard.fontManager.get_font("titillium_72");
    auto label = registry.create();
    auto &textC = registry.assign<Text>(label, shader, mesh, font, text);
    textC.set_color(256.f / 256, 256.f / 256, 256.f / 256);
    registry.assign<Transform>(label, pos.x, pos.y, 0., 0.3f, 0.3f);
    registry.assign<Label>(label, 1.0f);
}

#endif //PANDAEXPRESS_SCENE_HELPER_H
