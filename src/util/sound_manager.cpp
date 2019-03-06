//
// Created by Kenneth William on 2019-03-06.
//

#include "sound_manager.h"

SoundManager::SoundManager() {}


void SoundManager::init() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "Failed to initialize SDL Audio");

    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        fprintf(stderr, "Failed to open audio device");

    }
    m_background_music =  Mix_LoadMUS(audio_path("PE.ogg"));
    Mix_PlayMusic(m_background_music, -1);
}