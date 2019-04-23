//
// Created by Avery Brown on 2019-03-04.
//

#include "enemy_animation_system.h"
#include "components/panda.h"
#include "components/bread.h"
#include "components/ghost.h"
#include "components/jacko.h"
#include "components/llama.h"
#include "components/spit.h"
#include "components/timer.h"
#include "components/chases.h"
#include "components/dracula.h"
#include "components/seeks.h"
#include "components/boss.h"
#include "level/level_system.h"



EnemyAnimationSystem::EnemyAnimationSystem() {}

void EnemyAnimationSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {

    frameRate = 4.f;

    auto bread_view = registry.view<Bread, Sprite>();
    for (auto bread_entity: bread_view) {
        auto &bread = bread_view.get<Bread>(bread_entity);
        auto &sprite = bread_view.get<Sprite>(bread_entity);

        bool alive = registry.has<Interactable>(bread_entity);
        animateBread(alive, sprite);
    }


    auto ghost_view = registry.view<Ghost, Sprite>();
    for (auto ghost_entity: ghost_view) {
        auto &sprite = ghost_view.get<Sprite>(ghost_entity);

        animateGhost(sprite);
    }

    auto jacko_view = registry.view<Jacko, Chases, Boss, Sprite>();
    for (auto jacko_entity: jacko_view) {
        auto &sprite = jacko_view.get<Sprite>(jacko_entity);
        auto &boss = jacko_view.get<Boss>(jacko_entity);
        auto &chases = jacko_view.get<Chases>(jacko_entity);

        animateJacko(boss.alive, chases.evading, sprite);
    }
    auto spit_view = registry.view<Spit, Sprite>();
    for (auto spit_entity: spit_view) {
        auto &sprite = spit_view.get<Sprite>(spit_entity);

        animateSpit(sprite);
    }

    auto llama_view = registry.view<Llama, Sprite, Timer>();
    for (auto llama_entity: llama_view) {
        auto &llama = llama_view.get<Llama>(llama_entity);
        auto &sprite = llama_view.get<Sprite>(llama_entity);
        auto& timer = llama_view.get<Timer>(llama_entity);
        float curr_time = timer.get_curr_time();
        float target_time = timer.get_target_time("spit");

        bool alive = registry.has<Interactable>(llama_entity);
        animateLlama(alive, curr_time, target_time, sprite);
    }

    auto dracula_view = registry.view<Dracula, Boss, Sprite, Chases>();
    for (auto dracula_entity: dracula_view) {
        auto &sprite = dracula_view.get<Sprite>(dracula_entity);
        auto &boss = dracula_view.get<Boss>(dracula_entity);
        auto &chases = dracula_view.get<Chases>(dracula_entity);
        auto &dracula = dracula_view.get<Dracula>(dracula_entity);

        if (counter != animationTime) {
            animateDracula(boss.alive, chases.evading, dracula.shooter_count, sprite);
            draculaIndex++;
        }
    }

    auto boss_view = registry.view<Boss, Sprite>();
    for (auto boss_entity: boss_view) {
        auto &sprite = boss_view.get<Sprite>(boss_entity);
        auto &boss = boss_view.get<Boss>(boss_entity);

            if (!boss.alive) {
                if (registry.has<Jacko>(boss_entity)) {
                    animateJacko(boss.alive, false, sprite);
                } else if (registry.has<Dracula>(boss_entity)) {
                    if (counter != animationTime) {
                        animateDracula(boss.alive, false, 0, sprite);
                        draculaIndex++;
                    }
                }
            }
    }

    auto bat_view = registry.view<Seeks, Sprite>();
    for (auto dracula_entity: bat_view) {
        auto &sprite = bat_view.get<Sprite>(dracula_entity);
        auto &bat = bat_view.get<Seeks>(dracula_entity);

        animateBats(sprite);

    }

    counter = (int) animationTime;
    animationTime += frameRate*blackboard.delta_time;

}


void EnemyAnimationSystem::animateBread(bool alive, Sprite &sprite){
    int row;
    int breadFrames = 7;
    frameRate = 4.f;

    if (alive) {
        row = 1;
    } else {
        row = 2;
        frameRate = 15.f;
        breadFrames = 3;
    }
    int index = ((int) animationTime % breadFrames);

    vec2 uv1 = {index*breadWidth, breadHeight*(row-1) + 0.01f};
    vec2 uv2 = {(index+1)*breadWidth, (row)*breadHeight - 0.02f};
    sprite.set_uvs(uv1, uv2);
}

void EnemyAnimationSystem::animateLlama(bool alive, float currentTime, float targetTime, Sprite &sprite){
    frameRate = 6.f;
    int llamaFrames = 14;
    int row = 1;
    float i = 0.005f;

    if (!alive) {
        row = 3;
        i = 0.0f;
        frameRate = 10.f;
        llamaFrames = 5;
    } 

    float mod = fmod(currentTime, targetTime);
    int index = ((int) (mod*frameRate) % llamaFrames);
    vec2 uv1 = {index*llamaWidth +0.005f, llamaHeight*(row-1)};
    vec2 uv2 = {(index+1)*llamaWidth + 0.01f, (row*llamaHeight) - i};
    sprite.set_uvs(uv1, uv2);
}

void EnemyAnimationSystem::animateJacko(bool alive, bool evading, Sprite &sprite){
    frameRate = 4.f;
    int row;
    if (alive) {
        row = ((int) animationTime % 2);
        if (evading){
            row = 2;
        }
    } else {
        row = 3;
        frameRate = 20.f;
    }
    int index = ((int) animationTime % jackoFrames);
    vec2 uv1 = {index*jackoWidth, jackoHeight*row};
    vec2 uv2 = {(index+1)*jackoWidth, (1+row)*jackoHeight - 0.01f};
    sprite.set_uvs(uv1, uv2);
}

void EnemyAnimationSystem::animateGhost(Sprite &sprite){
    frameRate = 4.f;
    int index = ((int) animationTime % ghostFrames);
    vec2 uv1 = {index*ghostWidth, 0};
    vec2 uv2 = {(index+1)*ghostWidth , 1};
    sprite.set_uvs(uv1, uv2);
}

void EnemyAnimationSystem::animateSpit(Sprite &sprite){
    frameRate = 4.f;
    int index = ((int) animationTime % spitFrames);
    vec2 uv1 = {index*spitWidth, 0.f};
    vec2 uv2 = {(index+1)*spitWidth, spitHeight};
    sprite.set_uvs(uv1, uv2);
}

void EnemyAnimationSystem::animateDracula(bool alive, bool evading, int shooterCount, Sprite &sprite){
    frameRate = 4.f;
    int row;
    if (alive) {
        if (evading) {
            row = 2;

            frameRate = 6.f;
        } else if (shooterCount > 0){
            row = 3;
        } else {
            row = 1;
        }
    } else {
        row = 4;
    }
    draculaIndex = ((int) animationTime % draculaFrames);
    vec2 uv1 = {draculaIndex*draculaWidth, (row - 1)*draculaHeight + 0.005f};
    vec2 uv2 = {(draculaIndex+1)*draculaWidth, row*draculaHeight};
    sprite.set_uvs(uv1, uv2);
}

void EnemyAnimationSystem::animateBats(Sprite &sprite){
    frameRate = 5.f;
    int index = ((int) animationTime % batFrames);
    vec2 uv1 = {index*batWidth, 0.f};
    vec2 uv2 = {(index+1)*batWidth, batHeight};
    sprite.set_uvs(uv1, uv2);
}
