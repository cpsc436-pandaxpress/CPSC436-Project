//
// Created by Prayansh Srivastava on 2019-01-30.
//

#ifndef PANDAEXPRESS_CONSTANTS_H
#define PANDAEXPRESS_CONSTANTS_H


#include "project_path.hpp"
#define data_path PROJECT_SOURCE_DIR "data"
#define shaders_path(name) data_path "/shaders/" name
#define textures_path(name) data_path "/textures/" name
#define audio_path(name) data_path "/audio/" name
#define levels_path(name) data_path "/levels/" name
#define mesh_path(name) data_path "/meshes/" name
#define fonts_path(name) data_path "/fonts/" name

typedef int SceneID;
typedef int SFXID;
typedef int SceneType;

static const SFXID SFX_JUMP = 0;
static const SFXID SFX_JACKO_LAUGH = 1;
static const SFXID SFX_PANDA_HURT = 2;
static const SFXID SFX_TELEPORT = 3;
static const SFXID SFX_BAT_SHOT = 4;
static const SFXID SFX_DRACULA_HIT = 5;
static const SFXID SFX_DRACULA_LAUGH = 6;
static const SFXID SFX_DRACULA_DEATH = 7;
static const SFXID SFX_JACKO_HIT = 8;
static const SFXID SFX_JACKO_DEATH = 9;

static const SceneID MAIN_MENU_SCENE_ID   = 0;
static const SceneID STORY_EASY_JUNGLE_SCENE_ID  = 1;
static const SceneID STORY_EASY_SKY_SCENE_ID    = 2;
static const SceneID BOSS_SCENE_ID    = 3;
static const SceneID ENDLESS_JUNGLE_SCENE_ID = 4;
static const SceneID ENDLESS_SKY_SCENE_ID = 5;
static const SceneID STORY_BEACH_INTRO_SCENE_ID  = 6;
static const SceneID STORY_HARD_JUNGLE_SCENE_ID = 7;
static const SceneID STORY_HARD_SKY_SCENE_ID = 8;
static const SceneID STORY_JUNGLE_INTRO_SCENE_ID  = 9;
static const SceneID DRACULA_BOSS_SCENE_ID    = 10;

static const SceneID INVINCIBILITY_MUSIC = 15;
static const SceneID VAPE_HORIZONTAL_MUSIC = 16;
static const SceneID VAPE_VERTICAL_MUSIC = 17;


static const SceneType JUNGLE_TYPE = 0;
static const SceneType SKY_TYPE = 1;
static const SceneType BOSS_TYPE = 2;
static const SceneType STORY_TYPE = 3;
static const SceneType BOSS_DRACULA_TYPE = 4;

static const float DEFAULT_SPEED_MULTIPLIER = 1.0f;
static const float MAX_SPEED_MULTIPLIER = 1.5f;
static const float TIME_MULTIPLIER_SPEED = 0.001f;

#endif //PANDAEXPRESS_CONSTANTS_H
