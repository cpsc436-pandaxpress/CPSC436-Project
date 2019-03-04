//
// Created by Prayansh Srivastava on 2019-02-12.
//

#include <graphics/background.h>
#include <components/obeys_gravity.h>
#include <components/health.h>
#include <components/interactable.h>
#include <components/causes_damage.h>
#include <components/velocity.h>
#include <components/tutorial.h>
#include <graphics/text.h>
#include "horizontal_scene.h"
#include "util/constants.h"

HorizontalScene::HorizontalScene(Blackboard &blackboard, SceneManager &scene_manager) :
        Scene(scene_manager),
        level_system(),
        sprite_render_system(),
        sprite_transform_system(),
        background_transform_system(),
        background_render_system(),
        physics_system(),
        player_movement_system(HORIZONTAL_SCENE_ID),
        collision_system(),
        ghost_movement_system(),
        player_animation_system(HORIZONTAL_SCENE_ID)

{
    init_scene(blackboard);
    create_tutorial(blackboard);
    gl_has_errors();
}

void HorizontalScene::update(Blackboard &blackboard) {
    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_ESCAPE)) {
        blackboard.camera.set_position(0, 0);
        reset_scene(blackboard);
        change_scene(MAIN_MENU_SCENE_ID);
        return;
    }

    update_camera(blackboard);
    update_panda(blackboard);
    update_tutorial(blackboard);

    level_system.update(blackboard, registry_);
    background_transform_system.update(blackboard, registry_);
    player_movement_system.update(blackboard, registry_);
    collision_system.update(blackboard, registry_);
    physics_system.update(blackboard, registry_);
    sprite_transform_system.update(blackboard, registry_);
    ghost_movement_system.update(blackboard, registry_);
    player_animation_system.update(blackboard, registry_);
    timer_system.update(blackboard, registry_);
}

void HorizontalScene::update_panda(Blackboard &blackboard) {
    vec2 cam_position = blackboard.camera.position();
    vec2 cam_size = blackboard.camera.size();

    auto &transform = registry_.get<Transform>(panda_entity);
    auto &panda = registry_.get<Panda>(panda_entity);
    auto &panda_collidable = registry_.get<Collidable>(panda_entity);

    if (transform.x + panda_collidable.width < cam_position.x - cam_size.x / 2 ||
        transform.y - panda_collidable.height > cam_position.y + cam_size.y / 2 || !panda.alive) {
        reset_scene(blackboard);
    } else if (transform.x + panda_collidable.width / 2 > cam_position.x + cam_size.x / 2) {
        transform.x = cam_position.x + cam_size.x / 2 - panda_collidable.width / 2;
    }
}

void HorizontalScene::update_camera(Blackboard &blackboard) {
    vec2 cam_position = blackboard.camera.position();

    auto &panda_transform = registry_.get<Transform>(panda_entity);
    float y_offset = std::min(0.f, panda_transform.y + MAX_CAMERA_Y_DIFF);

    blackboard.camera.set_position(cam_position.x + CAMERA_SPEED * blackboard.delta_time,
                                   y_offset);
    blackboard.camera.compose();
}

void HorizontalScene::update_tutorial(Blackboard &blackboard) {
    float scaleY = 0.25;
    float scaleX = 0.25;
    auto &tutorial_trans = registry_.get<Transform>(tutorial2_entity);

    if (tutorial_trans.x + 100.f < blackboard.camera.position().x - blackboard.camera.size().x / 2.0 ){
        auto &tutorial_trans = registry_.replace<Transform>(tutorial_entity, -1500.f, -200.f, 0.f, scaleX, scaleY);
        auto &tutorial2_trans = registry_.replace<Transform>(tutorial2_entity, -1500.f,  -200.f, 0.f, scaleX, scaleY);
    }
}

void HorizontalScene::render(Blackboard &blackboard) {
    background_render_system.update(blackboard, registry_); // render background first
    sprite_render_system.update(blackboard, registry_);
}

void HorizontalScene::reset_scene(Blackboard &blackboard) {
    level_system.destroy_entities(registry_);
    registry_.destroy(panda_entity);
    for (uint32_t e: bg_entities) {
        registry_.destroy(e);
    }
    bg_entities.clear();
    init_scene(blackboard);
}

void HorizontalScene::init_scene(Blackboard &blackboard) {
    blackboard.randNumGenerator.init(0);
    blackboard.camera.set_position(CAMERA_START_X, CAMERA_START_Y);
    blackboard.camera.compose();
    create_background(blackboard);
    create_panda(blackboard);
    create_text(blackboard);
    level_system.init();
}

void HorizontalScene::create_panda(Blackboard &blackboard) {
    panda_entity = registry_.create();

    auto texture = blackboard.texture_manager.get_texture("panda_sprites");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    auto sprite = Sprite(texture, shader, mesh);


    float scaleY = 75.0 / texture.height();
    float scaleX = 75.0 / texture.width();
    registry_.assign<Transform>(panda_entity, PANDA_START_X, PANDA_START_Y, 0., scaleX, scaleY);
    registry_.assign<Sprite>(panda_entity, sprite);
    registry_.assign<Panda>(panda_entity);
    registry_.assign<ObeysGravity>(panda_entity);
    registry_.assign<Health>(panda_entity, 1);
    registry_.assign<Interactable>(panda_entity);
    registry_.assign<CausesDamage>(panda_entity, false, true, 1);
    registry_.assign<Velocity>(panda_entity, 0.f, 0.f);
    registry_.assign<Collidable>(panda_entity, texture.width() * scaleX, texture.height() * scaleY);
}

void HorizontalScene::create_background(Blackboard &blackboard) {
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
void HorizontalScene::create_tutorial(Blackboard &blackboard) {
    tutorial_entity = registry_.create();
    tutorial2_entity = registry_.create();

    auto texture =  blackboard.texture_manager.get_texture("tutorial");
    auto texture2 =  blackboard.texture_manager.get_texture("tutorial_bread");

    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    float scaleY = 0.25;
    float scaleX = 0.25;
    registry_.assign<Sprite>(tutorial_entity, texture, shader, mesh);
    registry_.assign<Tutorial>(tutorial_entity);
    registry_.assign<Transform>(tutorial_entity, 400.f, -200.f, 0., scaleX, scaleY);

    registry_.assign<Sprite>(tutorial2_entity, texture2, shader, mesh);
    registry_.assign<Tutorial>(tutorial2_entity);
    registry_.assign<Transform>(tutorial2_entity, 900.f, -200.f, 0., scaleX, scaleY);

}

void HorizontalScene::create_text(Blackboard &blackboard) {
    auto text = registry_.create();
    auto shader = blackboard.shader_manager.get_shader("text");
    FontType font = FontType();
    font.load(fonts_path("ocraext.ttf"), 24);

    GLuint vao, vbo, ibo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    bool result = !gl_has_errors();
    auto mesh = Mesh(vao, vbo, 0);
    vec3 color = {1.0f, 1.0f, 1.0f};
    printf("loading text: %s\n", (result) ? "true" : "false");

    registry_.assign<Text>(text, shader, mesh, font, color, 800.f, 450.f);
}





