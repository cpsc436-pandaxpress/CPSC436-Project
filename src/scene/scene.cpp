//
// Created by alex on 20/01/19.
//

#include "scene.h"
#include "scene_manager.h"

Scene::Scene(SceneManager &scene_manager) :
    scene_manager_(scene_manager),
    registry_()
{}

bool Scene::change_scene(SceneID id, bool reset) {
    return scene_manager_.change_scene(id, reset);
}

void Scene::set_mode(SceneMode mode) {
    mode_ = mode;
}
