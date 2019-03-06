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

void SoundManager::changeBackgroundMusic(SceneID id) {
if(id==BOSS_SCENE_ID){
        m_background_music = Mix_LoadMUS(audio_path("graveyard.ogg"));
    }else if(id==VERTICAL_SCENE_ID){
        m_background_music = Mix_LoadMUS(audio_path("vertical2.ogg"));
    }
    else{
        m_background_music = Mix_LoadMUS(audio_path("PE.ogg"));
    }
    Mix_PlayMusic(m_background_music, -1);
}

void SoundManager::playSFX(SFXID id) {
    if(id==SFX_JUMP){
        m_sfx = Mix_LoadWAV(audio_path("jump.wav"));
    }
    if(id==SFX_JACKO_LAUGH){
        m_sfx = Mix_LoadWAV(audio_path("JackoLaugh.wav"));
    }
    if(id==SFX_PANDA_HURT){
        m_sfx = Mix_LoadWAV(audio_path("PandaHurt.wav"));
    }
    Mix_PlayChannel(-1, m_sfx,0);
}