//
// Created by Avery Brown on 2019-04-13.
//


#include "story_jungle_animation_system.h"
#include "components/panda.h"
#include "components/kelly.h"
#include "components/timer.h"
#include "level/level_system.h"



StoryJungleAnimationSystem::StoryJungleAnimationSystem() {}

void StoryJungleAnimationSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {

    int row;

    auto panda_view = registry.view<Panda, Timer, Sprite>();
    for (auto panda_entity: panda_view) {
        auto &sprite = panda_view.get<Sprite>(panda_entity);

        auto &timer = panda_view.get<Timer>(panda_entity);
        float curr_time = timer.get_curr_time("end_scene");

        if (curr_time == 0.f) {
            resetScene();
        } else if ((int) animationTime == 0){
            animatePanda(0, row, sprite);
        } else if (counter != (int) animationTime) {
            if (pandaSunscreen < 27) {
                row = 1;
                pandaSunscreen++;
                if (pandaIndex == PANDAFRAMES) {
                    pandaIndex = 0;
                }
                if (pandaSunscreen == 27) {
                    break;
                }
            } else if (pandaHeartPumping <= 25){
                row = 2;
                pandaHeartPumping++;
                if (pandaIndex == PANDAFRAMES){
                    pandaIndex = 5;
                }
                if (pandaHeartPumping > 25) {
                    pandaIndex = 0;
                    break;
                }
            } else if (jackoEnters <= 25) {
                row = 3;
                jackoEnters++;

                if (pandaIndex == PANDAFRAMES) {
                    pandaIndex = 10;
                }

                if (jackoEnters == PANDAFRAMES) {
                    jackoGrabsKelly = true;
                    jackoIndex = 0;
//                    registry.destroy<Hearts>();
                }

                if (jackoEnters >  25) {
                    pandaIndex = 0;
                    break;
                }

            } else {
                row = 4;
                brokenHearted++;
                if (pandaIndex == PANDAFRAMES) {
                    pandaIndex = 9;
                }
            }
            if (pandaIndex < PANDAFRAMES) {
                animatePanda(pandaIndex, row, sprite);
                pandaIndex++;
            }
        }
    }


    auto kelly_view = registry.view<Kelly, Sprite>();
    for (auto kelly_entity: kelly_view) {
        auto &sprite = kelly_view.get<Sprite>(kelly_entity);
        animateKelly(sprite);
    }

    counter = (int) animationTime;
    animationTime += FRAMERATE * blackboard.delta_time;

}

void StoryJungleAnimationSystem::animatePanda(int index, int row, Sprite &sprite){
    vec2 uv1 = {index * PANDAWIDTH + 0.0055f, (row - 1)*PANDAHEIGHT + 0.003f};
    vec2 uv2 = {(index + 1) * PANDAWIDTH - 0.011f, row*PANDAHEIGHT - 0.075f};
    sprite.set_uvs(uv1, uv2);
}

void StoryJungleAnimationSystem::animateKelly(Sprite &sprite){
    int index = ((int) animationTime % KELLYFRAMES);
    vec2 uv1 = {index*KELLYWIDTH, 0.f};
    vec2 uv2 = {(index+1)*KELLYWIDTH, KELLYHEIGHT};
    sprite.set_uvs(uv1, uv2);
}

void StoryJungleAnimationSystem::resetScene() {
    animationTime = 0.f;
    counter = 0;
    pandaIndex = 0;
    jackoIndex = 0;
    pandaSunscreen = 0;
    pandaHeartPumping = 0;
    jackoEnters = 0;
    brokenHearted = 0;
    jackoGrabsKelly = false;
}
