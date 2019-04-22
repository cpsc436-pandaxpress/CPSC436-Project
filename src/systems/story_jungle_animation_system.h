//
// Created by Avery Brown on 2019-04-13.
//

#ifndef PANDAEXPRESS_STORY_JUNGLE_ANIMATION_SYSTEM_H
#define PANDAEXPRESS_STORY_JUNGLE_ANIMATION_SYSTEM_H

#include "system.h"

class StoryJungleAnimationSystem : public System {
public:
    StoryJungleAnimationSystem();

    int pandaGetsVape = 0;
    int pandaVapes = 0;

    virtual void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;

private:
    const float PANDAWIDTH = 0.1;
    const float PANDAHEIGHT = 0.16666;
    const float KELLYWIDTH = 0.20f;
    const float KELLYHEIGHT = 1.f;
    const float FRAMERATE = 4.f;
    const float VAPEHEIGHT = 1.f;
    const float VAPEWIDTH = 0.25;
    const int KELLYFRAMES = 5;
    const int VAPEFRAMES = 4;
    const int KELLYCALLSFORHELP = 18;
    const float VAPESPEED = 200.f;
    const int PANDASIGHS = 10;
    const int PANDARISES = 10;
    const int PANDASEESVAPE = 10;
    const int PANDARUNS = 20;
    const int PANDAHOLDSVAPE = 12;
    const int PANDAGETSVAPE = 30;
    const int PANDAVAPES = 8;

    float animationTime = 0.f;
    float pandaAnimationTime = 0.f;
    int counter = 0;
    int pandaCounter = 0;
    int pandaIndex = 0;
    int kellyIndex = 0;
    int pandaSighing = 0;
    int pandaHearsKelly = 0;
    int pandaRises = 0;
    int pandaSeesVape = 0;
    int pandaRuns = 0;
    bool kellyCallsForHelp = false;
    int kellyCallingForHelp = 0;
    bool vapeEnters = false;
    float pandaFrameRate = 4.f;

    void animatePanda(int row, Sprite &sprite);
    void animateKelly(Sprite &sprite);
    void animateVape(Sprite &sprite);
    void resetScene();

};

#endif //PANDAEXPRESS_STORY_JUNGLE_ANIMATION_SYSTEM_H
