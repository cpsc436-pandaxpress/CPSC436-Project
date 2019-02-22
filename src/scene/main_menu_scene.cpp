//
// Created by alex on 21/02/19.
//

#include "main_menu_scene.h"

static const int BUTTON_WIDTH = 320;
static const int BUTTON_HEIGHT = 100;
static const int BUTTON_PADDING = 40;

MainMenuScene::MainMenuScene(Blackboard& blackboard, SceneManager& scene_manager) :
    Scene(scene_manager),
    splash_sprite_(
        blackboard.textureManager.get_texture("splash"),
        blackboard.shader_manager.get_shader("sprite")
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



    int top_center_y = 0; //(int)(cam_size.y * 3 / 4) - (count * BUTTON_HEIGHT + (count-1) * BUTTON_PADDING) / 2;
    int center_x =  0; //(int)(cam_size.x / 2);

    for (auto i = 0; i < count; i++) {
        if (i == selected_button_) {
            button_sprites_[i].set_color(1.f, 0.3f, 0.7f);
            button_bg_sprites_[i].set_color(0.5f, 0.5f, 0.5f);
        }
        else {
            button_sprites_[i].set_color(0.5f, 0.5f, 0.5f);
            button_bg_sprites_[i].set_color(0.3f, 0.3f, 0.3f);
        }

        button_sprites_[i].set_size(BUTTON_WIDTH, BUTTON_HEIGHT);
        button_bg_sprites_[i].set_size(BUTTON_WIDTH, BUTTON_HEIGHT);
        auto vertical_offset = (BUTTON_HEIGHT + BUTTON_PADDING) * i;
        button_sprites_[i].set_pos(center_x, top_center_y + vertical_offset);
        button_bg_sprites_[i].set_pos(center_x, top_center_y + vertical_offset);
    }

    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_RETURN)) {
        change_scene(button_targets_[selected_button_]);
    }

}

void MainMenuScene::render(Blackboard& blackboard) {
    auto cam_size = blackboard.camera.size();
    blackboard.camera.set_position(cam_size.x / 2, cam_size.y / 2);

    auto& projection = blackboard.camera.get_projection();

    splash_sprite_.draw(projection);

    for (auto i = 0; i < button_sprites_.size(); i++) {
        //button_bg_sprites_[i].draw(projection);
        button_sprites_[i].draw(projection);
    }
}

void MainMenuScene::add_item(Blackboard& blackboard, char* texture_name, SceneID sceneID) {
    auto texture = blackboard.textureManager.get_texture(texture_name);
    auto bg_texture = blackboard.textureManager.get_texture("pixel");
    auto shader = blackboard.shader_manager.get_shader("sprite");

    auto sprite = Sprite(texture, shader);
    auto bg_sprite = Sprite(bg_texture, shader);

    button_sprites_.push_back(sprite);
    button_bg_sprites_.push_back(bg_sprite);
    button_y_positions_.push_back(0);
    button_targets_.push_back(sceneID);
}