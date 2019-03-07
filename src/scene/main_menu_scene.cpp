//
// Created by alex on 21/02/19.
//

#include "main_menu_scene.h"
#include <graphics/background.h>


static const int BUTTON_WIDTH = 350;
static const int BUTTON_HEIGHT = 120;
static const int BUTTON_PADDING = 40;

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
    button_targets_(),
    background_transform_system(),
    background_render_system()
{
}

void MainMenuScene::update(Blackboard& blackboard) {
    //set splash alignment
    auto cam_size = blackboard.camera.size();
    splash_sprite_.set_size((int)cam_size.x, (int)cam_size.y);
    splash_sprite_.set_pos(0, 0);

    background_transform_system.update(blackboard, registry_);

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



    int button_y = -250;
    int button_x =  200;

    for (auto i = 0; i < count; i++) {
        if (i == selected_button_) {
            button_sprites_[i].set_color(0.7f, 0.9f, 0.9f);
            button_bg_sprites_[i].set_color(0.5f, 0.5f, 0.5f);
        }
        else {
            button_sprites_[i].set_color(1.f, 1.f, 1.f);
            button_bg_sprites_[i].set_color(0.3f, 0.3f, 0.3f);
        }
//        float height = 75.0f / texture.height();
//        float width = 75.0f / texture.width();
        button_sprites_[i].set_size(BUTTON_WIDTH, BUTTON_HEIGHT);
        button_bg_sprites_[i].set_size(BUTTON_WIDTH, BUTTON_HEIGHT);
        auto vertical_offset = (BUTTON_HEIGHT + BUTTON_PADDING) * i;
        button_sprites_[i].set_pos(button_x, button_y + vertical_offset);
        button_bg_sprites_[i].set_pos(button_x, button_y + vertical_offset);
    }

    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_RETURN)) {
        change_scene(button_targets_[selected_button_]);
    }

}

void MainMenuScene::render(Blackboard& blackboard) {
    auto& projection = blackboard.camera.get_projection();

    splash_sprite_.draw(projection);

    for (auto i = 0; i < button_sprites_.size(); i++) {
        button_sprites_[i].draw(projection);
    }
}

void MainMenuScene::add_item(Blackboard& blackboard, char* texture_name, SceneID sceneID) {
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


void MainMenuScene::create_background(Blackboard &blackboard) {
    std::vector<Texture> textures;
    textures.reserve(4);
    // This order matters for rendering
    textures.push_back(blackboard.texture_manager.get_texture("bg_top"));
    textures.push_back(blackboard.texture_manager.get_texture("bg_front"));
    textures.push_back(blackboard.texture_manager.get_texture("bg_middle"));
    textures.push_back(blackboard.texture_manager.get_texture("bg_back"));
    // end order
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    int i = 0;
    for (Texture t: textures) {
        auto bg_entity = registry_.create();
        auto &bg = registry_.assign<Background>(bg_entity, t, shader, mesh, i);
        bg.set_pos1(0.0f, 0.0f);
        bg.set_pos2(blackboard.camera.size().x, 0.0f);
        bg.set_rotation_rad(0.0f);
        bg.set_scale(blackboard.camera.size().x / t.width(),
                     blackboard.camera.size().y / t.height());
        bg_entities.push_back(bg_entity);
        i++;
    }
}