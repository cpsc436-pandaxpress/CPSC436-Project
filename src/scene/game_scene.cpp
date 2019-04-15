//
// Created by Prayansh Srivastava on 2019-04-07.
//

#include "game_scene.h"

GameScene::GameScene(SceneManager &manager) : Scene(manager) {

}

void GameScene::create_panda(Blackboard &blackboard) {
    auto texture = blackboard.texture_manager.get_texture("panda_sprites");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    auto shaderHealth = blackboard.shader_manager.get_shader("health");
    auto meshHealth = blackboard.mesh_manager.get_mesh("health");

    float scaleY = 75.0f / texture.height();
    float scaleX = 75.0f / texture.width();
    vec2 size = {HEALTH_BAR_X_SIZE, HEALTH_BAR_Y_SIZE};
    vec2 scale = {0.6, 0.6};

    panda_entity = registry_.create();
    registry_.assign<Transform>(panda_entity, PANDA_START_X, PANDA_START_Y, 0., scaleX, scaleY);
    registry_.assign<Sprite>(panda_entity, texture, shader, mesh);
    registry_.assign<Panda>(panda_entity);
    registry_.assign<ObeysGravity>(panda_entity);
    registry_.assign<Health>(panda_entity, 3);
    registry_.assign<Interactable>(panda_entity);
    registry_.assign<CausesDamage>(panda_entity, PANDA_DMG_MASK, 1);
    registry_.assign<Velocity>(panda_entity, 0.f, 0.f);
    registry_.assign<Timer>(panda_entity);
    registry_.assign<Collidable>(panda_entity, texture.width() * scaleX,
                                 texture.height() * scaleY);
    registry_.assign<Layer>(panda_entity, PANDA_LAYER);
    auto &healthbar = registry_.assign<HealthBar>(panda_entity,
                                                  meshHealth, shaderHealth, size, scale);
    registry_.assign<HudElement>(panda_entity,
                                 vec2{size.x / 2.f * scale.x + HUD_HEALTH_X_OFFSET,
                                      blackboard.camera.size().y - HUD_Y_OFFSET});
}

void GameScene::create_score_text(Blackboard &blackboard) {
    FontType font = blackboard.fontManager.get_font("titillium_72");
    auto shader = blackboard.shader_manager.get_shader("text");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    std::string textVal = "0";

    auto score_entity = registry_.create();
    auto &text = registry_.assign<Text>(score_entity, shader, mesh, font, textVal);
    text.set_scale(0.8f);
    registry_.assign<Score>(score_entity);
    registry_.assign<HudElement>(score_entity,
                                 vec2{blackboard.camera.size().x - HUD_SCORE_X_OFFSET,
                                      blackboard.camera.size().y - HUD_Y_OFFSET});
    registry_.assign<Layer>(score_entity, TEXT_LAYER);
}

void GameScene::create_high_score_text(Blackboard &blackboard, int high_score) {
    FontType font = blackboard.fontManager.get_font("titillium_72");
    auto shader = blackboard.shader_manager.get_shader("text");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    auto high_score_entity = registry_.create();
    std::stringstream ss;
    ss << ". " << std::setfill('0') << std::setw(7) << high_score << ".";
    auto &text2 = registry_.assign<Text>(high_score_entity, shader, mesh, font, ss.str());
    text2.set_scale(0.8f);
    registry_.assign<HudElement>(high_score_entity,
                                 vec2{blackboard.camera.size().x / 2.0f - HUD_HEALTH_X_OFFSET,
                                      blackboard.camera.size().y - HUD_Y_OFFSET});
    registry_.assign<Layer>(high_score_entity, TEXT_LAYER);
}

void GameScene::create_fade_overlay(Blackboard &blackboard) {
    auto fade_overlay_entity = registry_.create();
    auto shaderFade = blackboard.shader_manager.get_shader("fade");
    auto meshFade = blackboard.mesh_manager.get_mesh("health");
    float height = blackboard.camera.size().y;
    float width = blackboard.camera.size().x;
    vec2 size = {width, height};
    auto &fade = registry_.assign<FadeOverlay>(fade_overlay_entity, meshFade, shaderFade, size);
    registry_.assign<Layer>(fade_overlay_entity, OVERLAY_LAYER);
}

void GameScene::create_pause_menu(Blackboard &blackboard) {
    pause_menu_entity = registry_.create();

    auto texture = blackboard.texture_manager.get_texture("pause_menu");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    registry_.assign<Sprite>(pause_menu_entity, texture, shader, mesh);
    registry_.assign<PauseMenu>(pause_menu_entity);
    registry_.assign<Layer>(pause_menu_entity, OVERLAY_LAYER);
}

void GameScene::cleanup() {
    registry_.destroy<Panda>();
    registry_.destroy<FadeOverlay>();
    registry_.destroy<Text>();
}