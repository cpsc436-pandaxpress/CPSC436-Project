//
// Created by alex on 20/01/19.
//

#pragma once

#include <entt/entity/registry.hpp>

#include "../util/blackboard.h"
#include "../util/input_manager.h"
#include "../util/constants.h"

// Simple int ID


//prototype declaration to avoid circular references
class SceneManager;

class Scene {
private:
    SceneManager& scene_manager_;

protected:
    entt::DefaultRegistry registry_;

public:
    Scene(SceneManager& scene_manager);

    // the "=0" denotes pure virtual functions
    // which establish the Scene class as abstract

    // update the scene
    virtual void update(Blackboard& blackboard) = 0;

    // render the scene
    virtual void render(Blackboard& blackboard) = 0;


protected:
    // wraps SceneManager::change_scene()
    bool change_scene(SceneID id);
};