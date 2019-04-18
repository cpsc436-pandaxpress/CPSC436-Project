//
// Created by Avery Brown on 2019-04-10.
//


#include "story_beach_animation_system.h"
#include "components/panda.h"
#include "components/kelly.h"
#include "components/jacko.h"
#include "components/hearts.h"
#include "components/timer.h"
#include "scene/story_intro_beach.h"
#include "level/level_system.h"



StoryBeachAnimationSystem::StoryBeachAnimationSystem() {}

void StoryBeachAnimationSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {

    int row;
    auto fade_view = registry.view<FadeOverlay, Timer>();
    for (auto fade_entity: fade_view) {
        auto &timer = fade_view.get<Timer>(fade_entity);
        float curr_time = timer.get_curr_time();

        if (curr_time == 0.f) {
            resetScene();
        }
    }

    auto panda_view = registry.view<Panda, Sprite>();
    for (auto panda_entity: panda_view) {
        auto &sprite = panda_view.get<Sprite>(panda_entity);

        if ((int) animationTime == 0){
            animatePanda(0, row, sprite);
        } else if (counter != (int) animationTime) {
            if (pandaSunscreen < PANDASUNCREENRUBS) {
                row = 1;
                pandaSunscreen++;
                if (pandaIndex == PANDAFRAMES) {
                    pandaIndex = 0;
                }
                if (pandaSunscreen == 27) {
                    break;
                }
            } else if (pandaHeartPumping <= PANDAHEARTPUMPS){
                row = 2;
                pandaHeartPumping++;
                if (pandaIndex == PANDAFRAMES){
                    pandaIndex = 5;
                }
                if (pandaHeartPumping > PANDAHEARTPUMPS) {
                    pandaIndex = 0;
                    break;
                }
            } else if (jackoEnters <= JACKOENTERING) {
                row = 3;
                jackoEnters++;

                if (pandaIndex == PANDAFRAMES) {
                    pandaIndex = 10;
                }

                if (jackoEnters == PANDAFRAMES) {
                    jackoGrabsKelly = true;
                    jackoIndex = 0;
                    registry.destroy<Hearts>();
                }

                if (jackoEnters >  JACKOENTERING) {
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
        if (jackoGrabsKelly) {
            registry.destroy(kelly_entity);
        } else {
            animateKelly(sprite);
        }
    }

    auto jacko_view = registry.view<Jacko, Velocity, Sprite>();
    for (auto jacko_entity: jacko_view) {
        auto &velocity = jacko_view.get<Velocity>(jacko_entity);
        auto &sprite = jacko_view.get<Sprite>(jacko_entity);
        if (jackoGrabsKelly) {
            velocity.x_velocity = JACKOSPEED;
            if (jackoIndex == JACKOFRAMES){
                jackoIndex = 5;
            }
        } else if (pandaHeartPumping == 20) {
            velocity.x_velocity = -JACKOSPEED;
        }
        if (!jackoGrabsKelly || counter != (int) animationTime) {
            animateJacko(jackoIndex, sprite);
        }
    }

    auto hearts_view = registry.view<Hearts, Sprite>();
    for (auto hearts_entity: hearts_view) {
        auto &sprite = hearts_view.get<Sprite>(hearts_entity);
        if (!jackoGrabsKelly) {
            animateHearts(sprite);
        }
    }

    counter = (int) animationTime;
    animationTime += FRAMERATE * blackboard.delta_time;

}


void StoryBeachAnimationSystem::animateJacko(int index, Sprite &sprite){
    int row;
    if (!jackoGrabsKelly) {
        row = ((int) animationTime % 2);
        index = ((int) animationTime % JACKOFRAMES);
    } else {
        row = 2;
        jackoIndex++;
    }
    vec2 uv1 = {index*JACKOWIDTH, JACKOHEIGHT*row};
    vec2 uv2 = {(index+1)*JACKOWIDTH - 0.005f, (1+row)*JACKOHEIGHT - 0.01f};
    sprite.set_uvs(uv1, uv2);
}

void StoryBeachAnimationSystem::animatePanda(int index, int row, Sprite &sprite){
    vec2 uv1 = {index * PANDAWIDTH + 0.0055f, (row - 1)*PANDAHEIGHT + 0.003f};
    vec2 uv2 = {(index + 1) * PANDAWIDTH - 0.011f, row*PANDAHEIGHT - 0.075f};
    sprite.set_uvs(uv1, uv2);
}

void StoryBeachAnimationSystem::animateKelly(Sprite &sprite){
    int index = ((int) animationTime % KELLYFRAMES);
    vec2 uv1 = {index*KELLYWIDTH, 0.f};
    vec2 uv2 = {(index+1)*KELLYWIDTH, KELLYHEIGHT};
    sprite.set_uvs(uv1, uv2);
}

void StoryBeachAnimationSystem::animateHearts(Sprite &sprite){
    int index = ((int) animationTime % HEARTSFRAMES);
    vec2 uv1 = {index*HEARTSWIDTH, 0.f};
    vec2 uv2 = {(index+1)*HEARTSWIDTH, HEARTSHEIGHT};
    sprite.set_uvs(uv1, uv2);
}

void StoryBeachAnimationSystem::resetScene() {
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

