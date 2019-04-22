//
// Created by Prayansh Srivastava on 2019-02-12.
//

#include "boss_scene.h"
#include "util/constants.h"
#include <graphics/fade_overlay.h>

BossScene::BossScene(Blackboard &blackboard, SceneManager &scene_manager) :
        GameScene(scene_manager),
        level_system(false),
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
        hud_transform_system(),
        transition_system(BOSS_TYPE)
{
    init_scene(blackboard);
    reset_scene(blackboard); // idk why??? but this is required
    create_fade_overlay(blackboard);
    gl_has_errors();
}

void BossScene::update(Blackboard &blackboard) {
    if (!initialized) {
        initial_update(blackboard);
    }
    auto &panda = registry_.get<Panda>(panda_entity);
    auto &interactable = registry_.get<Interactable>(panda_entity);
    auto &fadeOverlay = registry_.get<FadeOverlay>(fade_overlay_entity);
    if (blackboard.camera.transition_ready) {
        if (fadeOverlay.alpha() < 1.2f) {
            fade_overlay_system.update(blackboard, registry_);
        } else {
            go_to_next_scene(blackboard);
            return;
        }
    }
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
        blackboard.story_health = MAX_HEALTH;
        blackboard.story_lives = MAX_LIVES;
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


        if (fadeOverlay.alpha() > 0.f) {
            fade_overlay_system.update(blackboard, registry_);
        }

        auto& jacko_health = registry_.get<Health>(jacko_entity);
        auto& boss = registry_.get<Boss>(jacko_entity);

        if (jacko_health.health_points <= 0 && !blackboard.camera.in_transition) {
            generate_cave(1250,200, blackboard, registry_);
            blackboard.camera.in_transition = true;
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
        transition_system.update(blackboard, registry_);
        timer_system.update(blackboard, registry_);
        scene_timer.update(blackboard.delta_time);
        falling_platform_system.update(blackboard, registry_);
        background_transform_system.update(blackboard, registry_);
        hud_transform_system.update(blackboard, registry_); // should run last
    } else {
        pause_menu_transform_system.update(blackboard, registry_);
    }

    update_cave(blackboard, registry_, 10);
    update_shake_effect(blackboard);
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
        if (mode_ == ENDLESS) {
            reset_scene(blackboard);
        } else if (blackboard.story_lives > 1) {
            blackboard.story_lives -= 1;
            blackboard.story_health = MAX_HEALTH;
            reset_scene(blackboard);
        } else {
            blackboard.story_health = MAX_HEALTH;
            blackboard.story_lives = MAX_LIVES;
            blackboard.camera.set_position(0, 0);
            reset_scene(blackboard);
            change_scene(MAIN_MENU_SCENE_ID);
            return;
        }
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
    create_lives_text(blackboard);
    auto &fadeOverlay = registry_.get<FadeOverlay>(fade_overlay_entity);
    fadeOverlay.set_alpha(1.0);
    level_system.init(registry_);
    blackboard.post_process_shader = std::make_unique<Shader>(blackboard.shader_manager.get_shader("sprite"));
}

void BossScene::initial_update(Blackboard &blackboard) {
    reset_scene(blackboard);
    initialized = true;
}

void BossScene::reset_scene(Blackboard &blackboard) {
    cleanup();
    blackboard.camera.in_transition = false;
    blackboard.camera.transition_ready = false;
    if (scene_timer.exists(SHAKE_LABEL) && !scene_timer.is_done(SHAKE_LABEL)) {
        scene_timer.remove(SHAKE_LABEL);
    }
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
    registry_.assign<Boss>(jacko_entity);
    registry_.assign<Chases>(jacko_entity, target);
    registry_.assign<Health>(jacko_entity, 1);
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

void BossScene::go_to_next_scene(Blackboard &blackboard) {
    auto &health = registry_.get<Health>(panda_entity);
    blackboard.story_health = health.health_points;
    cleanup();
    blackboard.camera.in_transition = false;
    blackboard.camera.transition_ready = false;
    change_scene(STORY_HARD_JUNGLE_SCENE_ID);
}

void BossScene::generate_cave(float x, float y, Blackboard &blackboard, entt::DefaultRegistry &registry) {
    create_shake_effect(blackboard);
    auto cave = registry.create();
    auto shaderCave = blackboard.shader_manager.get_shader("cave");
    auto meshCave = blackboard.mesh_manager.get_mesh("cave");
    registry.assign<Transform>(cave, x, y, 0., 80, 80);
    registry.assign<Interactable>(cave);
    float heightCave = 750.f;
    float widthCave = 750.f;
    vec2 sizeCave = {widthCave, heightCave};
    vec2 scaleCave = {-80, 80};
    auto &caveE = registry.assign<Cave>(cave, meshCave, shaderCave, sizeCave, scaleCave, true);
    caveE.set_pos(x, y);
    registry.assign<Layer>(cave, TERRAIN_LAYER - 5);

    auto caveEntrance = registry.create();
    auto shaderCaveEntrance = blackboard.shader_manager.get_shader("caveEntrance");
    auto meshCaveEntrance = blackboard.mesh_manager.get_mesh("caveEntrance");
    registry.assign<Transform>(caveEntrance, x, y, 0.f, 80, 80);
    registry.assign<Interactable>(caveEntrance);
    float heightCave_entrance = 2 * 80;
    float widthCave_entrance = 2 * 80;
    vec2 sizeCave_entrance = {widthCave_entrance, heightCave_entrance};
    vec2 scaleCave_entrance = {80, 80};
    registry.assign<Collidable>(caveEntrance, heightCave_entrance, widthCave_entrance);
    auto &caveEntranceE = registry.assign<CaveEntrance>(caveEntrance, meshCaveEntrance, shaderCaveEntrance,
                                                        sizeCave_entrance, scaleCave_entrance);
    caveEntranceE.set_pos(x + 700, y);
    registry.assign<Layer>(caveEntrance, TERRAIN_LAYER - 4);
}

void BossScene::update_cave(Blackboard &blackboard, entt::DefaultRegistry &registry, int speed){
    if (scene_timer.exists("SHAKE")) {
        auto cave_view = registry.view<Cave, Transform>();
        for (auto cave_entity : cave_view) {
            auto &cave = cave_view.get<Cave>(cave_entity);
            auto &cave_transform = cave_view.get<Transform>(cave_entity);
            if (cave.pos().y > -550) {
                cave.set_pos(cave.pos().x, cave.pos().y - speed);
            } else {
                cave.growing = false;
            }
        }
        auto cave_entrance_view = registry.view<CaveEntrance, Transform>();
        for (auto cave_entrance_entity : cave_entrance_view) {
            auto &cave_entrance = cave_entrance_view.get<CaveEntrance>(cave_entrance_entity);
            auto &cave_transform = cave_entrance_view.get<Transform>(cave_entrance_entity);
            if (cave_entrance.pos().y > -550) {
                cave_entrance.set_pos(cave_entrance.pos().x, cave_entrance.pos().y - speed);
            }
        }
    }
}

void BossScene::create_shake_effect(Blackboard &blackboard) {
    scene_timer.save_watch("SHAKE", SHAKE);
    blackboard.post_process_shader = std::make_unique<Shader>(
            blackboard.shader_manager.get_shader("shake"));
}

void BossScene::update_shake_effect(Blackboard &blackboard) {
    if (scene_timer.exists("SHAKE")) {
        float val = ((3*(scene_timer.get_target_time("SHAKE") - scene_timer.get_curr_time()) /
                      SHAKE)); // Ratio of time done (Ranges from [1...0])
        blackboard.post_process_shader->bind();
        blackboard.post_process_shader->set_uniform_float("time", val);
        blackboard.post_process_shader->unbind();
        // Setup new timeElapsed Uniform
        if (scene_timer.is_done("SHAKE")) {
            blackboard.post_process_shader = std::make_unique<Shader>(
                    blackboard.shader_manager.get_shader("sprite"));
            scene_timer.remove("SHAKE");
        }
    }
}