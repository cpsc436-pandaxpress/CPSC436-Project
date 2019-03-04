//
// Created by Prayansh Srivastava on 2019-01-30.
//

#ifndef PANDAEXPRESS_CONSTANTS_H
#define PANDAEXPRESS_CONSTANTS_H

#include <scene/scene.h>
#include "project_path.hpp"
#define data_path PROJECT_SOURCE_DIR "data"
#define shaders_path(name) data_path "/shaders/" name
#define textures_path(name) data_path "/textures/" name
#define audio_path(name) data_path "/audio/" name
#define levels_path(name) data_path "/levels/" name
#define fonts_path(name) data_path "/fonts/" name

static const SceneID MAIN_MENU_SCENE_ID   = 0;
static const SceneID HORIZONTAL_SCENE_ID  = 1;
static const SceneID VERTICAL_SCENE_ID    = 2;
static const SceneID BOSS_SCENE_ID    = 3;

#endif //PANDAEXPRESS_CONSTANTS_H
