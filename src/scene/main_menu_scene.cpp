//
// Created by alex on 21/02/19.
//

#include "main_menu_scene.h"
#include <graphics/background.h>




MainMenuScene::MainMenuScene(Blackboard& blackboard, SceneManager& scene_manager) :
    Scene(scene_manager),
    splash_sprite_(
        blackboard.texture_manager.get_texture("splash"),
        blackboard.shader_manager.get_shader("sprite"),
        blackboard.mesh_manager.get_mesh("sprite")
    ),
    button_width_(0),
    button_height_(0),
    button_sprites_(),
    button_bg_sprites_(),
    button_y_positions_(),
    button_targets_()
{
}

void MainMenuScene::update(Blackboard& blackboard) {
    //set splash alignment
    auto cam_size = blackboard.camera.size();
    splash_sprite_.set_size((int)cam_size.x, (int)cam_size.y);
    splash_sprite_.set_pos(0, 0);

    //set button alignment
    int count = button_sprites_.size();

    if (count == 0) {
        return;
    }

    if (selected_button_ < 0) {
        selected_button_ = 0;
    }

    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_UP)) {
        if (selected_button_ == 0) {
            selected_button_ = count - 1;
        }
        else {
            selected_button_--;
        }
    }
    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_DOWN)) {
        selected_button_ ++;
        selected_button_ %= count;
    }

    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_ESCAPE)) {
        blackboard.input_manager.signal_exit();
    }


    for (auto i = 0; i < count; i++) {
        if (i == selected_button_) {
            button_sprites_[i].set_color(1.f, 1.f, 1.f);
            button_bg_sprites_[i].set_color(0.3f, 0.3f, 0.3f);
        }
        else {
            button_sprites_[i].set_color(0.7f, 0.9f, 0.9f);
            button_bg_sprites_[i].set_color(0.5f, 0.5f, 0.5f);
        }
        button_sprites_[i].set_size(BUTTON_WIDTH, BUTTON_HEIGHT);
        button_bg_sprites_[i].set_size(BUTTON_WIDTH, BUTTON_HEIGHT);
        auto vertical_offset = (BUTTON_HEIGHT + BUTTON_PADDING) * i;
        button_sprites_[i].set_pos(BUTTON_X, BUTTON_Y + vertical_offset);
        button_bg_sprites_[i].set_pos(BUTTON_X, BUTTON_Y + vertical_offset);
    }

    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_RETURN)) {
        change_scene(button_targets_[selected_button_], true);
    }

    // Hidden scene access
    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_5)) {
        change_scene(STORY_EASY_JUNGLE_SCENE_ID, true);
    }
    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_6)) {
        change_scene(STORY_EASY_SKY_SCENE_ID, true);
    }
    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_7)) {
        change_scene(BOSS_SCENE_ID, true);
    }
    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_8)) {
        change_scene(STORY_HARD_JUNGLE_SCENE_ID, true);
    }
    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_9)) {
        change_scene(STORY_HARD_SKY_SCENE_ID, true);
    }
    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_0)) {
        change_scene(DRACULA_BOSS_SCENE_ID, true);
    }
}

void MainMenuScene::render(Blackboard& blackboard) {
    auto& projection = blackboard.camera.get_projection();

    blackboard.window.draw((Renderable*)&splash_sprite_, projection);

    for (auto i = 0; i < button_sprites_.size(); i++) {
        blackboard.window.draw((Renderable*)&(button_sprites_[i]), projection);
    }
}

void MainMenuScene::add_item(Blackboard& blackboard, const char* texture_name, SceneID sceneID) {
    auto texture = blackboard.texture_manager.get_texture(texture_name);
    auto bg_texture = blackboard.texture_manager.get_texture("pixel");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");


    auto sprite = Sprite(texture, shader, mesh);
    auto bg_sprite = Sprite(bg_texture, shader, mesh);

    button_sprites_.push_back(sprite);
    button_bg_sprites_.push_back(bg_sprite);
    button_y_positions_.push_back(0);
    button_targets_.push_back(sceneID);
}

void MainMenuScene::reset_scene(Blackboard &blackboard) {

}
