//
// Created by alex on 20/01/19.
//

#pragma once

#include "entt/entity/registry.hpp"


// Simple int ID
typedef uint32_t SceneID;

//prototype declaration to avoid circular references
class SceneManager;

class Scene {
private:
    SceneManager& scene_manager_;

protected:
    entt::registry<uint32_t> registry_;

public:
    Scene(SceneManager& manager);

    // the "=0" denotes pure virtual functions
    // which establish Scene class as abstract

    // update the scene
    virtual void update(float delta_time) = 0;

    // render the scene
    // TODO: define better
    virtual void render() = 0;


protected:
    // wraps SceneManager::change_scene()
    bool change_scene(SceneID id);
};