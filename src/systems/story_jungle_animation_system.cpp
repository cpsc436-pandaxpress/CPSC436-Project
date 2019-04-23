//
// Created by Avery Brown on 2019-04-13.
//


#include "story_jungle_animation_system.h"
#include "components/panda.h"
#include "components/kelly.h"
#include "components/timer.h"
#include "components/vape.h"
#include "level/level_system.h"



StoryJungleAnimationSystem::StoryJungleAnimationSystem() {}

void StoryJungleAnimationSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {

    int row, pandaFrames, pandaStartIndex;

    auto panda_view = registry.view<Panda, Timer, Sprite, Velocity>();
    for (auto panda_entity: panda_view) {
        auto &sprite = panda_view.get<Sprite>(panda_entity);
        auto &velocity = panda_view.get<Velocity>(panda_entity);

        auto &timer = panda_view.get<Timer>(panda_entity);
        float curr_time = timer.get_curr_time();

        if (curr_time == 0.f) {
            resetScene();
        } else if ((int) pandaAnimationTime == 0) {
            animatePanda(row, sprite);
        } else if (pandaCounter != (int) pandaAnimationTime) {
            if (pandaSighing < PANDASIGHS) {
                pandaFrameRate = 1.f;
                row = 1;
                pandaFrames = 4;
                pandaSighing++;
                pandaStartIndex = 0;

                if (pandaSighing == PANDASIGHS) {
                    kellyCallsForHelp = true;
                }

            } else if (pandaHearsKelly < KELLYCALLSFORHELP) {
                pandaFrameRate = 5.f;
                row = 2;
                pandaFrames = 6;
                pandaHearsKelly++;
                pandaStartIndex = 3;
                if (pandaHearsKelly == 1) {
                    pandaIndex = 0;
                    pandaFrameRate = 5.f;
                }

            } else if (pandaRises < PANDARISES) {
                pandaFrameRate = 2.f;
                row = 3;
                pandaFrames = 10;
                pandaRises++;
                pandaStartIndex = 6;
                if (pandaIndex == pandaStartIndex){
                    velocity.x_velocity = 300.f;
                } else if (pandaIndex == pandaFrames - 1){
                    velocity.x_velocity = 0.f;
                }
                if (pandaRises == 1) {
                    pandaIndex = 0;
                }
            } else if (pandaSeesVape < PANDASEESVAPE) {
                pandaFrameRate = 1.5f;
                row = 4;
                pandaSeesVape++;
                if (!vapeEnters) {
                    pandaStartIndex = 0;
                    pandaFrames = 3;
                } else {
                    pandaStartIndex = 8;
                    pandaFrames = 10;
                }
                if (pandaSeesVape < 5) {
                    pandaIndex = 0;
                }
                if (pandaIndex == 1) {
                    velocity.x_velocity = 0.f;
                }
                if (pandaSeesVape == 1) {
                    vapeEnters = true;
                    pandaIndex = 0;
                }

            } else if (pandaGetsVape < PANDAGETSVAPE) {
                if (pandaGetsVape == 0) {
                    registry.destroy<Vape>();
                }
                pandaFrameRate = 5.f;
                row = 5;
                pandaFrames = 5;
                pandaGetsVape++;
                pandaStartIndex = 2;

                if (pandaGetsVape < PANDAHOLDSVAPE) {
                    pandaIndex = 0;
                }

            } else if (pandaVapes < PANDAVAPES){
                pandaFrameRate = 2.f;
                row = 5;
                pandaFrames = 10;
                pandaVapes++;
                pandaStartIndex = 9;
                if (pandaVapes == 1) {
                    pandaIndex = 5;
                }
            } else if (pandaRuns < PANDARUNS) {
                pandaFrameRate = 7.f;
                row = 6;
                pandaFrames = 10;
                pandaRuns++;
                pandaStartIndex = 5;
                if (pandaIndex == 3) {
                    velocity.x_velocity = 750.f;
                }
                if (pandaRuns == 1) {
                    pandaIndex = 0;
                }

            }
             if (pandaIndex >= pandaFrames - 1) {
                 pandaIndex = pandaStartIndex;
                }
             animatePanda(row, sprite);
             pandaIndex++;
        }
    }

    auto kelly_view = registry.view<Kelly, Sprite>();
    for (auto kelly_entity: kelly_view) {
        auto &sprite = kelly_view.get<Sprite>(kelly_entity);
        if (kellyCallingForHelp >= KELLYCALLSFORHELP) {
            kellyCallsForHelp = false;
        }
        if ((int) animationTime == 0 || counter != (int) animationTime){
            animateKelly(sprite);
        }
    }

    auto vape_view = registry.view<Vape, Sprite, Velocity>();
    for (auto vape_entity: vape_view) {
        auto &sprite = vape_view.get<Sprite>(vape_entity);
        auto &velocity = vape_view.get<Velocity>(vape_entity);

        if (vapeEnters) {
            velocity.y_velocity = VAPESPEED;
        }

        animateVape(sprite);
    }

    counter = (int) animationTime;
    animationTime += FRAMERATE * blackboard.delta_time;
    pandaCounter = (int) pandaAnimationTime;
    pandaAnimationTime += pandaFrameRate * blackboard.delta_time;

}

void StoryJungleAnimationSystem::animatePanda(int row, Sprite &sprite){
    vec2 uv1 = {pandaIndex * PANDAWIDTH, (row - 1)*PANDAHEIGHT + 0.015f};
    vec2 uv2 = {(pandaIndex + 1) * PANDAWIDTH - 0.015f, row*PANDAHEIGHT};
    sprite.set_uvs(uv1, uv2);
}

void StoryJungleAnimationSystem::animateKelly(Sprite &sprite){
    if (kellyCallsForHelp) {
        if (kellyIndex >= KELLYFRAMES) {
            kellyIndex = 1;
        }
        kellyCallingForHelp++;
    } else {
        kellyIndex = 0;
    }
    vec2 uv1 = {kellyIndex*KELLYWIDTH, 0.f};
    vec2 uv2 = {(kellyIndex+1)*KELLYWIDTH, KELLYHEIGHT};
    sprite.set_uvs(uv1, uv2);
    kellyIndex++;
}

void StoryJungleAnimationSystem::animateVape(Sprite &sprite){
    int index = ((int) animationTime % VAPEFRAMES);
    vec2 uv1 = {index*VAPEWIDTH, 0.f};
    vec2 uv2 = {(index+1)*VAPEWIDTH, VAPEHEIGHT};
    sprite.set_uvs(uv1, uv2);
}

void StoryJungleAnimationSystem::resetScene() {
    animationTime = 0.f;
    pandaAnimationTime = 0.f;
    counter = 0;
    pandaCounter = 0;
    pandaIndex = 0;
    kellyIndex = 0;
    pandaSighing = 0;
    pandaHearsKelly = 0;
    pandaRises = 0;
    pandaSeesVape = 0;
    pandaRuns = 0;
    kellyCallsForHelp = false;
    kellyCallingForHelp = 0;
    vapeEnters = false;
    pandaFrameRate = 4.f;
    pandaGetsVape = 0;
    pandaVapes = 0;
}
