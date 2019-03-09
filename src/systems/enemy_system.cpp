//
// Created by Rebecca Roth on 2019-03-03.
//

#include "enemy_system.h"

EnemySystem::EnemySystem():
        ghost_movement_system()
{};

void EnemySystem::update(Blackboard &blackboard, entt::DefaultRegistry& registry, SceneID sceneid) {
    vec2 cam_position = blackboard.camera.position();
    vec2 cam_size = blackboard.camera.size();

    ghost_movement_system.update(blackboard, registry, sceneid);
    handle_bread(cam_position, cam_size, sceneid, blackboard, registry);
    handle_ghosts(cam_position, cam_size, sceneid, blackboard, registry);
    handle_llamas(cam_position, cam_size, sceneid, blackboard, registry);
    handle_spit(cam_position, cam_size, sceneid, blackboard, registry);
}

void EnemySystem::generate_projectile(float x, float y, bool spit_left, Blackboard &blackboard,
                                      entt::DefaultRegistry &registry) {
    auto texture = blackboard.texture_manager.get_texture("spit");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    auto scale = static_cast<float>(CELL_WIDTH / texture.width()/ 2);
    auto projectile = registry.create();
    registry.assign<Transform>(projectile, x, y - 30, 0., scale,
                               scale);
    registry.assign<Sprite>(projectile, texture, shader, mesh);
    registry.assign<Spit>(projectile);
    registry.assign<CausesDamage>(projectile, ALL_DMG_MASK, 1);
    registry.assign<Health>(projectile,1);
    if (spit_left)
        registry.assign<Velocity>(projectile, PROJECTILE_SPEED_X, PROJECTILE_SPEED_Y);
    else
        registry.assign<Velocity>(projectile, -PROJECTILE_SPEED_X, PROJECTILE_SPEED_Y);
    registry.assign<Interactable>(projectile);
    registry.assign<Collidable>(projectile, texture.width() * scale,
                                texture.height() * scale);
}

void EnemySystem::handle_bread(vec2 cam_position, vec2 cam_size, SceneID sceneid, Blackboard &blackboard, entt::DefaultRegistry &registry){
    auto bread_view = registry.view<Bread, Transform, Velocity, Collidable>();
    for (auto enemy_entity : bread_view) {
        auto &bread = bread_view.get<Bread>(enemy_entity);
        auto &bread_transform = bread_view.get<Transform>(enemy_entity);
        auto &bread_velocity = bread_view.get<Velocity>(enemy_entity);
        auto &bread_collidable = bread_view.get<Collidable>(enemy_entity);

        if (sceneid == HORIZONTAL_SCENE_ID) {
            if (bread_transform.x + bread_collidable.width < cam_position.x - cam_size.x / 2 ||
                bread_transform.y - bread_collidable.height > cam_position.y + cam_size.y / 2 + VERTICAL_BUFFER) {
                registry.destroy(enemy_entity);
                break;
            }
            else if (!bread.started) {
                if (bread_transform.x + bread_collidable.width / 2 < cam_position.x + cam_size.x / 2) {
                    bread_velocity.x_velocity = -BREAD_SPEED;
                }
            }
        }
        else if (sceneid == VERTICAL_SCENE_ID) {
            if (bread_transform.x + bread_collidable.width < cam_position.x - cam_size.x / 2 ||
                bread_transform.y - bread_collidable.height > cam_position.y + cam_size.y / 2 ||
                bread_transform.x + bread_collidable.width / 2 > cam_position.x + cam_size.x / 2) {
                registry.destroy(enemy_entity);
                break;
            }
            else if (!bread.started) {
                if (bread_transform.y + bread_collidable.height < cam_position.y - cam_size.y) {
                    if (bread.left)
                        bread_velocity.x_velocity = -BREAD_SPEED;
                    else
                        bread_velocity.x_velocity = BREAD_SPEED;
                }
            }
        }
    }
}

void EnemySystem::handle_ghosts(vec2 cam_position, vec2 cam_size, SceneID sceneid, Blackboard &blackboard, entt::DefaultRegistry &registry){
    auto ghost_view = registry.view<Ghost, Transform, Collidable>();
    for (auto enemy_entity : ghost_view) {
        auto &ghost = ghost_view.get<Ghost>(enemy_entity);
        auto &ghost_transform = ghost_view.get<Transform>(enemy_entity);
        auto &ghost_collidable = ghost_view.get<Collidable>(enemy_entity);

        if (sceneid == HORIZONTAL_SCENE_ID) {
            if (ghost_transform.x + ghost_collidable.width < cam_position.x - cam_size.x / 2 ||
                ghost_transform.y - ghost_collidable.height > cam_position.y + cam_size.y / 2 + VERTICAL_BUFFER) {
                registry.destroy(enemy_entity);
                break;
            }
        } else if (sceneid == VERTICAL_SCENE_ID) {
            if (ghost_transform.x + ghost_collidable.width < cam_position.x - cam_size.x / 2 ||
                ghost_transform.y - ghost_collidable.height > cam_position.y + cam_size.y / 2) {
                registry.destroy(enemy_entity);
                break;
            }
        }
    }
}

void EnemySystem::handle_llamas(vec2 cam_position, vec2 cam_size, SceneID sceneid, Blackboard &blackboard, entt::DefaultRegistry &registry) {
    auto llama_view = registry.view<Llama, Transform, Collidable, Timer>();
    for (auto enemy_entity : llama_view) {
        auto &llama = llama_view.get<Llama>(enemy_entity);
        auto &llama_transform = llama_view.get<Transform>(enemy_entity);
        auto &llama_collidable = llama_view.get<Collidable>(enemy_entity);
        auto &llama_timer = llama_view.get<Timer>(enemy_entity);

        if (sceneid == HORIZONTAL_SCENE_ID) {
            if (llama_transform.x + llama_collidable.width < cam_position.x - cam_size.x / 2 ||
                llama_transform.y - llama_collidable.height > cam_position.y + cam_size.y / 2 + VERTICAL_BUFFER) {
                registry.destroy(enemy_entity);
                break;
            }

            if (!llama.alive)
                break;

            if (llama_timer.is_done(SPIT_TIMER_LABEL)) {
                generate_projectile(llama_transform.x, llama_transform.y, true, blackboard, registry);
                llama_timer.reset_watch(SPIT_TIMER_LABEL);
            }
        } else if (sceneid == VERTICAL_SCENE_ID) {
            auto pandas_view = registry.view<Panda, Transform>();

            if (llama_transform.x + llama_collidable.width < cam_position.x - cam_size.x / 2 ||
                llama_transform.y - llama_collidable.height > cam_position.y + cam_size.y / 2 ||
                llama_transform.x + llama_collidable.width / 2 > cam_position.x + cam_size.x / 2) {
                registry.destroy(enemy_entity);
                break;
            }

            if (!llama.alive)
                break;

            for (auto panda_entity : pandas_view) {
                auto &pa_transform = pandas_view.get<Transform>(panda_entity);
                if (pa_transform.x <= llama_transform.x) {
                    llama_transform.x_scale = abs(llama_transform.x_scale);
                    if (llama_timer.is_done(SPIT_TIMER_LABEL)) {
                        generate_projectile(llama_transform.x, llama_transform.y, true, blackboard, registry);
                        llama_timer.reset_watch(SPIT_TIMER_LABEL);
                    }
                } else {
                    llama_transform.x_scale = -abs(llama_transform.x_scale);
                    if (llama_timer.is_done(SPIT_TIMER_LABEL)) {
                        generate_projectile(llama_transform.x, llama_transform.y, false, blackboard, registry);
                        llama_timer.reset_watch(SPIT_TIMER_LABEL);
                    }
                }
            }
        }
    }
}

void EnemySystem::handle_spit(vec2 cam_position, vec2 cam_size, SceneID sceneid, Blackboard &blackboard, entt::DefaultRegistry &registry){
    auto spit_view = registry.view<Spit, Transform, Collidable>();
    for (auto enemy_entity : spit_view) {
        auto &spit = spit_view.get<Spit>(enemy_entity);
        auto &spit_transform = spit_view.get<Transform>(enemy_entity);
        auto &spit_collidable = spit_view.get<Collidable>(enemy_entity);

        if (sceneid == HORIZONTAL_SCENE_ID) {
            if (spit_transform.x + spit_collidable.width < cam_position.x - cam_size.x / 2 ||
                spit_transform.y - spit_collidable.height > cam_position.y + cam_size.y / 2 + VERTICAL_BUFFER) {
                registry.destroy(enemy_entity);
                break;
            }
        } else if (sceneid == VERTICAL_SCENE_ID) {
            if (spit_transform.x + spit_collidable.width < cam_position.x - cam_size.x / 2 ||
                spit_transform.y - spit_collidable.height > cam_position.y + cam_size.y / 2 ||
                spit_transform.x + spit_collidable.width / 2 > cam_position.x + cam_size.x / 2) {
                registry.destroy(enemy_entity);
                break;
            }
        }
    }
}