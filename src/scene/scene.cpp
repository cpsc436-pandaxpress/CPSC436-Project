//
// Created by alex on 20/01/19.
//

#include "scene.h"
#include "scene_manager.h"

Scene::Scene(SceneManager &manager) :
    scene_manager_(manager),
    registry_()
{}

bool Scene::change_scene(SceneID id) {
    return scene_manager_.change_scene(id);
}