//
// Created by Kenneth William on 2019-03-06.
//

#include "sound_manager.h"

SoundManager::SoundManager() {}

SoundManager::~SoundManager() {
    for (auto music : m_background_music) {
        Mix_FreeMusic(music.second);
    }

    for (auto sfx : m_sfx) {
        Mix_FreeChunk(sfx.second);
    }

    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    Mix_Quit();
    Mix_CloseAudio();
}

void SoundManager::init() {
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "Failed to initialize SDL Audio");
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        fprintf(stderr, "Failed to open audio device");

    }

    m_sfx[SFX_JUMP] = Mix_LoadWAV(audio_path("jump.wav"));
    m_sfx[SFX_JACKO_LAUGH] = Mix_LoadWAV(audio_path("JackoLaugh.wav"));
    m_sfx[SFX_PANDA_HURT] = Mix_LoadWAV(audio_path("PandaHurt.wav"));

    m_background_music[MAIN_MENU_SCENE_ID] = Mix_LoadMUS(audio_path("PE.ogg"));
    m_background_music[STORY_EASY_JUNGLE_SCENE_ID] = Mix_LoadMUS(audio_path("PE.ogg"));
    m_background_music[ENDLESS_JUNGLE_SCENE_ID] = Mix_LoadMUS(audio_path("PE.ogg"));
    m_background_music[STORY_HARD_JUNGLE_SCENE_ID] = Mix_LoadMUS(audio_path("PE.ogg"));
    m_background_music[STORY_EASY_SKY_SCENE_ID] = Mix_LoadMUS(audio_path("vertical2.ogg"));
    m_background_music[ENDLESS_SKY_SCENE_ID] = Mix_LoadMUS(audio_path("vertical2.ogg"));
    m_background_music[STORY_EASY_SKY_SCENE_ID] = Mix_LoadMUS(audio_path("vertical2.ogg"));
    m_background_music[BOSS_SCENE_ID] = Mix_LoadMUS(audio_path("graveyard.ogg"));

    Mix_PlayMusic(m_background_music[MAIN_MENU_SCENE_ID], -1);
}

void SoundManager::changeBackgroundMusic(SceneID id) {
    Mix_PlayMusic(m_background_music[id], -1);
}

void SoundManager::playSFX(SFXID id) {
    Mix_PlayChannel(id, m_sfx[id], 0);
}