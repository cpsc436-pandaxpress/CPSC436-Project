//
// Created by Avery Brown on 2019-04-10.
//


#include "story_animation_system.h"
#include "components/panda.h"
#include "components/kelly.h"
#include "components/jacko.h"
#include "components/hearts.h"
#include "components/timer.h"
#include "level/level_system.h"



StoryAnimationSystem::StoryAnimationSystem() {}

void StoryAnimationSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {

    frameRate = 4.f;
    int row;

    auto panda_view = registry.view<Panda, Sprite>();
    for (auto panda_entity: panda_view) {
        auto &sprite = panda_view.get<Sprite>(panda_entity);

        if (animationTime == 0.f || (pandaIndex < PANDAFRAMES && counter != (int) animationTime)) {
            if (pandaSunscreen <= 23) {
                row = 1;
                pandaSunscreen++;
                if (pandaIndex == PANDAFRAMES - 1) {
                    pandaIndex = 0;
                }
            } else if (pandaheartPumping <= 20){
                row = 2;
                pandaheartPumping++;
                if (pandaIndex == PANDAFRAMES -1){
                    pandaIndex = 5;
                }
                if (pandaheartPumping == 20) {
                    pandaIndex = 0;
                }
            } else if (jackoEnters <= 13) {
                row = 3;
                jackoEnters++;
                if (jackoEnters == 13) {
                    pandaIndex = 0;
                }
            } else if (brokenHearted <= 13) {
                row = 4;
                brokenHearted++;
            }
            animatePanda(pandaIndex, row, sprite);
        }
    }


    auto kelly_view = registry.view<Kelly, Sprite>();
    for (auto kelly_entity: kelly_view) {
        auto &sprite = kelly_view.get<Sprite>(kelly_entity);

        animateKelly(sprite);
    }

//    auto jacko_view = registry.view<Jacko, Sprite>();
//    for (auto jacko_entity: jacko_view) {
//        auto &jacko = jacko_view.get<Jacko>(jacko_entity);
//        auto &sprite = jacko_view.get<Sprite>(jacko_entity);
//
//        animateJacko(sprite);
//
//    }

    auto hearts_view = registry.view<Hearts, Sprite>();
    for (auto hearts_entity: hearts_view) {
        auto &sprite = hearts_view.get<Sprite>(hearts_entity);

        animateHearts(sprite);
    }

    counter = (int) animationTime;
    animationTime += frameRate * blackboard.delta_time;

}


void StoryAnimationSystem::animateJacko(Sprite &sprite){
    frameRate = 4.f;
    int row = 1;
    int index = ((int) animationTime % JACKOFRAMES);
    vec2 uv1 = {index*JACKOWIDTH, JACKOHEIGHT*row};
    vec2 uv2 = {(index+1)*JACKOWIDTH, (1+row)*JACKOHEIGHT - 0.01f};
    sprite.set_uvs(uv1, uv2);
}

void StoryAnimationSystem::animatePanda(int index, int row, Sprite &sprite){
    frameRate = 3.f;
    vec2 uv1 = {index * PANDAWIDTH + 0.0007f, (row - 1)*PANDAHEIGHT + 0.01f};
    vec2 uv2 = {(index + 1) * PANDAWIDTH - 0.002f, row*PANDAHEIGHT - 0.05f};
    sprite.set_uvs(uv1, uv2);
    pandaIndex++;
}

void StoryAnimationSystem::animateKelly(Sprite &sprite){
    frameRate = 5.f;
    int index = ((int) animationTime % KELLYFRAMES);
    vec2 uv1 = {index*KELLYWIDTH, 0.f};
    vec2 uv2 = {(index+1)*KELLYWIDTH, KELLYHEIGHT};
    sprite.set_uvs(uv1, uv2);
}

void StoryAnimationSystem::animateHearts(Sprite &sprite){
    frameRate = 3.f;
    int index = ((int) animationTime % HEARTSFRAMES);
    vec2 uv1 = {index*HEARTSWIDTH, 0.f};
    vec2 uv2 = {(index+1)*HEARTSWIDTH, HEARTSHEIGHT};
    sprite.set_uvs(uv1, uv2);
}

