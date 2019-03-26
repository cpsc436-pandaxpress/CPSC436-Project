//
// Created by alex on 21/02/19.
//

#ifndef PANDAEXPRESS_MAIN_MENU_SCENE_H
#define PANDAEXPRESS_MAIN_MENU_SCENE_H

#include <cinttypes>
#include <vector>
#include <systems/background_render_system.h>
#include <systems/background_transform_system.h>
#include "../systems/sprite_render_system.h"
#include "../systems/sprite_transform_system.h"
#include "../util/blackboard.h"
#include "../systems/player_animation_system.h"
#include "../systems/enemy_animation_system.h"
#include "scene.h"



class MainMenuScene : public Scene {
private:
    Sprite splash_sprite_;
    uint32_t button_width_, button_height_;
    std::vector<Sprite> button_sprites_;
    std::vector<Sprite> button_bg_sprites_;
    std::vector<uint32_t> button_y_positions_;
    std::vector<SceneID> button_targets_;
    int selected_button_ = -1;

public:
    MainMenuScene(Blackboard& blackboard, SceneManager& scene_manager);

    virtual void update(Blackboard& blackboard) override;

    virtual void render(Blackboard& blackboard) override;

    void add_item(Blackboard& blackboard, char* texture_name, SceneID sceneID);
};

#endif //PANDAEXPRESS_MAIN_MENU_SCENE_H
