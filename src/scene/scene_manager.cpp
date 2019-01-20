//
// Created by alex on 20/01/19.
//

#include <entt/entity/registry.hpp>

#include "scene_manager.h"

SceneManager::SceneManager() :
    scenes_(),
    current_scene_(0),
    current_scene_set_(false)
{}

bool SceneManager::add_scene(SceneID id, Scene *scene) {
    if (scenes_.count(id) > 0) {
        return false;
    }
    else {
        scenes_.insert(std::pair<SceneID, Scene*>(id, scene));
        return true;
    }
}

bool SceneManager::change_scene(SceneID id) {
    if (scenes_.count(id) == 0) {
        return false;
    }
    else {
        current_scene_ = id;
        current_scene_set_ = true;
        return true;
    }
}

void SceneManager::update(float delta_time) {
    if (current_scene_set_) {
        scenes_[current_scene_]->update(delta_time);
    }
}