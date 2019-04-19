//
// Created by Prayansh Srivastava on 2019-02-12.
//

#include "boss_scene.h"
#include "util/constants.h"

BossScene::BossScene(Blackboard &blackboard, SceneManager &scene_manager) :
        GameScene(scene_manager),
        level_system(),
        background_transform_system(BOSS_TYPE),
        physics_system(),
        player_movement_system(BOSS_TYPE),
        chase_system(),
        jacko_ai_system(blackboard, registry_),
        player_animation_system(BOSS_TYPE),
        timer_system(),
        panda_dmg_system(),
        falling_platform_system(),
        enemy_animation_system(),
        health_bar_transform_system(),
        fade_overlay_system(),
        pause_menu_transform_system(),
        hud_transform_system()
{
    init_scene(blackboard);
    reset_scene(blackboard); // idk why??? but this is required
    gl_has_errors();
}

void BossScene::update(Blackboard &blackboard) {
    auto &panda = registry_.get<Panda>(panda_entity);
    auto &interactable = registry_.get<Interactable>(panda_entity);

    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_ESCAPE)) {
        if (pause) {
            pause = false;
            registry_.destroy(pause_menu_entity);
        } else {
            pause = true;
            create_pause_menu(blackboard);
        }
    } else if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_RETURN) && pause) {
        blackboard.camera.set_position(0, 0);
        reset_scene(blackboard);
        registry_.destroy(pause_menu_entity);
        change_scene(MAIN_MENU_SCENE_ID);
        pause = false;
        return;
    }

    if (!pause) {
        if (panda.alive && !panda.dead) {
            update_camera(blackboard);
            player_movement_system.update(blackboard, registry_);
        } else if (!panda.alive && interactable.grounded) {
            fade_overlay_system.update(blackboard, registry_);
        }

        // TODO: CHANGE THIS!
        // This is a temporary way of advancing to the next level
        auto& jacko_health = registry_.get<Health>(jacko_entity);
        if (jacko_health.health_points <= 0) {
            change_scene(STORY_HARD_JUNGLE_SCENE_ID);
        }

        update_panda(blackboard);

        level_system.update(blackboard, registry_);
        chase_system.update(blackboard, registry_);
        physics_system.update(blackboard, registry_);
        panda_dmg_system.update(blackboard, registry_);
        health_bar_transform_system.update(blackboard, registry_);
        jacko_ai_system.update(blackboard, registry_);
        sprite_transform_system.update(blackboard, registry_);
        player_animation_system.update(blackboard, registry_);
        enemy_animation_system.update(blackboard, registry_);
        timer_system.update(blackboard, registry_);
        falling_platform_system.update(blackboard, registry_);
        background_transform_system.update(blackboard, registry_);
        hud_transform_system.update(blackboard, registry_); // should run last
    } else {
        pause_menu_transform_system.update(blackboard, registry_);
    }
}

void BossScene::render(Blackboard &blackboard) {
    blackboard.window.colorScreen(vec3{30.f, 55.f, 153.f});
    render_system.update(blackboard, registry_);
}

void BossScene::update_panda(Blackboard &blackboard) {
    vec2 cam_position = blackboard.camera.position();
    vec2 cam_size = blackboard.camera.size();

    auto &transform = registry_.get<Transform>(panda_entity);
    auto &panda = registry_.get<Panda>(panda_entity);
    auto &panda_collidable = registry_.get<Collidable>(panda_entity);

    if (transform.y - panda_collidable.height > cam_position.y + cam_size.y / 2 || panda.dead) {
        reset_scene(blackboard);
    }
}

void BossScene::update_camera(Blackboard &blackboard) {
    auto &panda_transform = registry_.get<Transform>(panda_entity);
    float y_offset = std::min(0.f, panda_transform.y + MAX_CAMERA_Y_DIFF);

    blackboard.camera.set_position(panda_transform.x, y_offset);
    blackboard.camera.compose();
}

void BossScene::init_scene(Blackboard &blackboard) {
    blackboard.randNumGenerator.init(0);
    blackboard.camera.set_position(CAMERA_START_X, CAMERA_START_Y);
    blackboard.camera.compose();
    create_background(blackboard);
    create_panda(blackboard);
    create_jacko(blackboard, panda_entity);
    create_fade_overlay(blackboard);
    level_system.init(registry_);
    blackboard.post_process_shader = std::make_unique<Shader>(blackboard.shader_manager.get_shader("sprite"));
}

void BossScene::reset_scene(Blackboard &blackboard) {
    cleanup();
    init_scene(blackboard);
}

void BossScene::cleanup() {
    level_system.destroy_entities(registry_);
    registry_.destroy(jacko_entity);
    for (uint32_t e: bg_entities) {
        registry_.destroy(e);
    }
    bg_entities.clear();
    GameScene::cleanup();
}

void BossScene::create_jacko(Blackboard &blackboard, uint32_t target) {
    jacko_entity = registry_.create();

    auto texture = blackboard.texture_manager.get_texture("jacko");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    float scaleY = 200.0f / texture.height();
    float scaleX = 200.0f / texture.width();
    registry_.assign<Transform>(jacko_entity, -300, -300, 0., scaleX, scaleY);
    registry_.assign<Sprite>(jacko_entity, texture, shader, mesh);
    registry_.assign<Jacko>(jacko_entity);
    registry_.assign<Chases>(jacko_entity, target);
    registry_.assign<Health>(jacko_entity, 10);
    registry_.assign<Interactable>(jacko_entity);
    registry_.assign<CausesDamage>(jacko_entity, TOP_VULNERABLE_MASK, 1);
    registry_.assign<Velocity>(jacko_entity, 0.f, 0.f);
    registry_.assign<Collidable>(jacko_entity,
                                 texture.width() * scaleX * 0.75,
                                 texture.height() * scaleY
    );
    registry_.assign<Layer>(jacko_entity, BOSS_LAYER);

    auto shaderHealth = blackboard.shader_manager.get_shader("health");
    auto meshHealth = blackboard.mesh_manager.get_mesh("health");
    vec2 size = {HEALTH_BAR_X_SIZE, HEALTH_BAR_Y_SIZE};
    vec2 scale = {0.3, 0.3};
    auto &healthbar = registry_.assign<HealthBar>(jacko_entity,
                                                  meshHealth, shaderHealth, size, scale);
}

void BossScene::create_background(Blackboard &blackboard) {
    std::vector<Texture> textures;
    textures.reserve(4);
    // This order matters for rendering
    textures.push_back(blackboard.texture_manager.get_texture("grave_top"));
    textures.push_back(blackboard.texture_manager.get_texture("grave_middle"));
    textures.push_back(blackboard.texture_manager.get_texture("grave_front"));
    textures.push_back(blackboard.texture_manager.get_texture("grave_back"));
    // end order
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    int i = 0;
    int indices[4] = {3, 1, 2, 0};
    for (Texture t: textures) {
        auto bg_entity = registry_.create();
        auto &bg = registry_.assign<Background>(bg_entity, t, shader, mesh, indices[i], indices[i] == 3);
        registry_.assign<Layer>(bg_entity, BACKGROUND_LAYER - i);
        bg.set_pos1(0.0f, 0.0f);
        bg.set_rotation_rad(0.0f);
        bg.set_scale(blackboard.camera.size().x / t.width(),
                     blackboard.camera.size().y / t.height());
        bg_entities.push_back(bg_entity);
        i++;
    }

}