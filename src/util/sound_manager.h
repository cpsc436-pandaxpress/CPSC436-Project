//
// Created by Kenneth William on 2019-03-06.
//

#ifndef PANDAEXPRESS_SOUND_MANAGER_H
#define PANDAEXPRESS_SOUND_MANAGER_H



#include <SDL.h>
#include <SDL_mixer.h>
#include <sstream>
#include "util/constants.h"

class SoundManager {
public:
    SoundManager();
    void init();
    void changeBackgroundMusic(SceneID id);
    void playSFX(SFXID id);
private:
    Mix_Music* m_background_music;
    Mix_Chunk* m_sfx;
};


#endif //PANDAEXPRESS_SOUND_MANAGER_H
