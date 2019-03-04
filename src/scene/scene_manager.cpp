//
// Created by alex on 20/01/19.
//

#include <entt/entity/registry.hpp>
#include "util/constants.h"
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
        if (SDL_Init(SDL_INIT_AUDIO) < 0)
        {
            fprintf(stderr, "Failed to initialize SDL Audio");

        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
        {
            fprintf(stderr, "Failed to open audio device");

        }
        Mix_Music* m_background_music;

        if(id==3){
            m_background_music = Mix_LoadMUS(audio_path("graveyard.ogg"));
        }else if(id==2){
            m_background_music = Mix_LoadMUS(audio_path("CC.ogg"));
        }
        else{
            m_background_music = Mix_LoadMUS(audio_path("PE.ogg"));
        }



        Mix_PlayMusic(m_background_music, -1);
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