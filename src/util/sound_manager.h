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

private:
    Mix_Music* m_background_music;
};


#endif //PANDAEXPRESS_SOUND_MANAGER_H
