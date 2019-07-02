//
// Created by Kenneth William on 2019-03-06.
//

#ifndef PANDAEXPRESS_SOUND_MANAGER_H
#define PANDAEXPRESS_SOUND_MANAGER_H



#include <SDL.h>
#include <SDL_mixer.h>
#include <sstream>
#include "util/constants.h"
#include <unordered_map>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();
    void init();
    void changeBackgroundMusic(SceneID id);
    void playSFX(SFXID id);
    SceneID currentStage;
private:
    std::unordered_map<SceneID, Mix_Music*> m_background_music;
    std::unordered_map<SFXID, Mix_Chunk*> m_sfx;
};


#endif //PANDAEXPRESS_SOUND_MANAGER_H
