//
// Created by alex on 20/01/19.
//

#pragma once

#include <unordered_map>
#include <SDL.h>
#include <SDL_mixer.h>
#include <sstream>
#include "scene.h"
#include "../util/blackboard.h"


class SceneManager {
private:
    std::unordered_map<SceneID, Scene*> scenes_;

    bool current_scene_set_ = false;

public:
    SceneManager();
    SceneID current_scene_;
    // adds scene to scenes_ with key of id
    // DOES NOT manage memory of provided scene, should be done elsewhere
    // fails and returns false if another scene exists with the given ID
    // returns true otherwise
    bool add_scene(SceneID id, Scene* scene);

    // attempts to change current scene to one with given id
    // if called during update(), will switch scenes after current update()
    // fails and returns false if no such scene exists
    // returns true otherwise
    bool change_scene(SceneID id);

    // attempts to update the current scene, if one exists
    void update(Blackboard& blackboard);

    // attempts to render the current scene, if one exists
    void render(Blackboard& blackboard);
};
