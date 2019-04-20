//
// Created by Avery Brown on 2019-04-19.
//


#include "story_end_animation_system.h"
#include "components/panda.h"
#include "components/kelly.h"
#include "components/timer.h"
#include "components/vape.h"
#include "level/level_system.h"



StoryEndAnimationSystem::StoryEndAnimationSystem() {}

void StoryEndAnimationSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {

    int row, kellyFrames, kellyStartIndex, pandaFrames, pandaStartIndex;

    auto panda_view = registry.view<Panda, Sprite, Timer>();
    for (auto panda_entity: panda_view) {
        auto &sprite = panda_view.get<Sprite>(panda_entity);

        auto &timer = panda_view.get<Timer>(panda_entity);
        float curr_time = timer.get_curr_time();

        if (curr_time == 0.f) {
            resetScene();
        }
        if (pandaAnimationTime == 0.f || pandaCounter != (int) pandaAnimationTime) {
            if (pandaRunning < PANDARUNS){
                pandaFrames = 3;
                pandaRunning++;
                pandaStartIndex = 0;
            }
            if (pandaIndex == pandaFrames) {
                pandaIndex = pandaStartIndex;
            }
            animatePanda(sprite);
            pandaIndex++;
        }
    }

    auto kelly_view = registry.view<Kelly, Sprite>();
    for (auto kelly_entity: kelly_view) {
        auto &sprite = kelly_view.get<Sprite>(kelly_entity);
        if (kellyAnimationTime == 0.f || kellyCounter != (int) kellyAnimationTime) {
            if (kellySighing < KELLYSIGHS) {
                kellyFrameRate = 1.f;
                row = 1;
                kellyFrames = 2;
                kellySighing++;
                kellyStartIndex = 0;
            } else if (kellyGetsUp < KELLYGETSUP) {
                kellyFrameRate = 4.f;
                row = 1;
                kellyFrames = 6;
                kellyGetsUp++;
                kellyStartIndex = 5;
                if (kellyGetsUp == 1) {
                    kellyIndex = 2;
                }
            } else if (pandaHugging < PANDAHUG) {
                kellyFrameRate = 3.f;
                row = 2;
                kellyFrames = 4;
                pandaHugging++;
                kellyStartIndex = 1;
                if (pandaHugging == 1) {
                    kellyIndex = 0;
                    registry.destroy<Panda>();
                }
            }
            if (kellyIndex == kellyFrames) {
                kellyIndex = kellyStartIndex;
            }
            animateKelly(row, sprite);
            kellyIndex++;
        }
    }

    kellyCounter = (int) kellyAnimationTime;
    kellyAnimationTime += kellyFrameRate * blackboard.delta_time;
    pandaCounter = (int) pandaAnimationTime;
    pandaAnimationTime += pandaFrameRate * blackboard.delta_time;

}

void StoryEndAnimationSystem::animatePanda(Sprite &sprite){
    vec2 uv1 = {pandaIndex * PANDAWIDTH + 0.01f, 0.f};
    vec2 uv2 = {(pandaIndex + 1) * PANDAWIDTH, PANDAHEIGHT};
    sprite.set_uvs(uv1, uv2);
}

void StoryEndAnimationSystem::animateKelly(int row, Sprite &sprite){
    vec2 uv1 = {kellyIndex*KELLYWIDTH, (row-1)*KELLYHEIGHT};
    vec2 uv2 = {(kellyIndex+1)*KELLYWIDTH, row*KELLYHEIGHT};
    sprite.set_uvs(uv1, uv2);
}

void StoryEndAnimationSystem::resetScene() {
    kellyAnimationTime = 0.f;
    pandaCounter = 0;
    kellyCounter = 0;
    pandaIndex = 0;
    kellyIndex = 0;
    kellySighing = 0;
    kellyGetsUp = 0;
    pandaHugging = 0;
    pandaFrameRate = 5.f;
    kellyFrameRate = 4.f;
}
