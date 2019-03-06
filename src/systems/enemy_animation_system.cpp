//
// Created by Avery Brown on 2019-03-04.
//

#include "enemy_animation_system.h"
#include "components/bread.h"
#include "components/ghost.h"
#include "components/jacko.h"
#include "components/llama.h"
#include "components/spit.h"
#include "components/timer.h"
#include "level_system.h"



EnemyAnimationSystem::EnemyAnimationSystem() {}

void EnemyAnimationSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {

    frameRate = 4.f;

    auto bread_view = registry.view<Bread, Sprite>();
    for (auto bread_entity: bread_view) {
        auto &bread = bread_view.get<Bread>(bread_entity);
        auto &sprite = bread_view.get<Sprite>(bread_entity);
        animateBread(sprite);
    }

    auto ghost_view = registry.view<Ghost, Sprite>();
    for (auto ghost_entity: ghost_view) {
        auto &ghost = ghost_view.get<Ghost>(ghost_entity);
        auto &sprite = ghost_view.get<Sprite>(ghost_entity);
        animateGhost(sprite);
    }

    auto jacko_view = registry.view<Jacko, Sprite>();
    for (auto jacko_entity: jacko_view) {
        auto &bread = jacko_view.get<Jacko>(jacko_entity);
        auto &sprite = jacko_view.get<Sprite>(jacko_entity);
        animateJacko(sprite);
    }
    auto spit_view = registry.view<Spit, Sprite>();
    for (auto spit_entity: spit_view) {
        auto &bread = spit_view.get<Spit>(spit_entity);
        auto &sprite = spit_view.get<Sprite>(spit_entity);
        animateSpit(sprite);
    }

    auto llama_view = registry.view<Llama, Sprite, Timer>();
    for (auto llama_entity: llama_view) {
        auto &llama = llama_view.get<Llama>(llama_entity);
        auto &sprite = llama_view.get<Sprite>(llama_entity);
        auto& timer = llama_view.get<Timer>(llama_entity);
        float target_time = timer.watches["spit"].target_time;
        float time = timer.curr_time;
        animateLlama(time, target_time, sprite);
    }

    animationTime += frameRate*blackboard.delta_time;

}


void EnemyAnimationSystem::animateBread(Sprite &sprite){
    int index = ((int) animationTime % breadFrames);
    vec2 uv1 = {index*breadWidth, index*breadHeight};
    vec2 uv2 = {(index+1)*breadWidth, (index+1)*breadHeight};
    sprite.set_uvs(uv1, uv2);
}

void EnemyAnimationSystem::animateLlama(float time, float target_time, Sprite &sprite){
    frameRate = 8.f;

    int row = 1;
    float i = 0.065f;
//    if is facing left {
//        row = 2;
//        i = 0.035f;
//    }

    float mod = fmod(time, target_time);
    int index = ((int) (mod*frameRate) % llamaFrames);
//    int index = ((int) (animationTime) % llamaFrames);
    printf("%f \n", time);
    vec2 uv1 = {index*llamaWidth, 0.5f*(row-1)};
    vec2 uv2 = {(index+1)*llamaWidth, (row*llamaHeight) - i};
    sprite.set_uvs(uv1, uv2);
}

void EnemyAnimationSystem::animateJacko(Sprite &sprite){
    int index = ((int) animationTime % jackoFrames);
    int row = ((int) animationTime % 2);
    vec2 uv1 = {index*jackoWidth, jackoHeight*row};
    vec2 uv2 = {(index+1)*jackoWidth, (1+row)*jackoHeight};
    sprite.set_uvs(uv1, uv2);
}

void EnemyAnimationSystem::animateGhost(Sprite &sprite){
    int index = ((int) animationTime % ghostFrames);
    vec2 uv1 = {index*ghostWidth + 0.005f, index*ghostHeight};
    vec2 uv2 = {(index+1)*ghostWidth + 0.005f, (1+index)*ghostHeight};
    sprite.set_uvs(uv1, uv2);
}

void EnemyAnimationSystem::animateSpit(Sprite &sprite){
    int index = ((int) animationTime % spitFrames);
    vec2 uv1 = {index*spitWidth, 0.f};
    vec2 uv2 = {(index+1)*spitWidth, spitHeight};
    sprite.set_uvs(uv1, uv2);
}
