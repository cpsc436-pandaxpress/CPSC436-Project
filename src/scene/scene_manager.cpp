//
// Created by alex on 20/01/19.
//

#include <entt/entity/registry.hpp>
#include "util/constants.h"
#include "scene_manager.h"


SceneManager::SceneManager(Blackboard& blackboard) :
    scenes_(),
    current_scene_(0),
    current_scene_set_(false),
    blackboard(blackboard)
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

bool SceneManager::change_scene(SceneID id, bool reset) {
    if (scenes_.count(id) == 0) {
        return false;
    }
    else {
        current_scene_ = id;
        current_scene_set_ = true;
        blackboard.soundManager.changeBackgroundMusic(id);

        if (scene_modes_.count(id) > 0) {
            scenes_[id]->set_mode(scene_modes_[id]);
        }
        if (reset) {
            scenes_[id]->reset_scene(blackboard);
        }

        return true;
    }
}


void SceneManager::update(Blackboard& blackboard) {
    if (current_scene_set_) {
        scenes_[current_scene_]->update(blackboard);
    }

}

void SceneManager::render(Blackboard& blackboard) {
    if (current_scene_set_) {
        scenes_[current_scene_]->render(blackboard);
    }
}

bool SceneManager::add_scene(SceneID id, Scene* scene, SceneMode mode) {
    if (scenes_.count(id) > 0 || scene_modes_.count(id) > 0) {
        return false;
    }
    else {
        scenes_[id] = scene;
        scene_modes_[id] = mode;
        return true;
    }
}
