//
// Created by Avery Brown on 2019-04-10.
//

#ifndef PANDAEXPRESS_STORY_ANIMATION_SYSTEM_H
#define PANDAEXPRESS_STORY_ANIMATION_SYSTEM_H


#include "system.h"

class StoryAnimationSystem : public System {
public:
    StoryAnimationSystem();

    virtual void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;

private:
    const float PANDAWIDTH = 0.0769;
    const float PANDAHEIGHT = 0.25f;
    const float KELLYWIDTH = 0.1f;
    const float KELLYHEIGHT = 1.f;
    const float JACKOWIDTH = 0.1f;
    const float JACKOHEIGHT = 1.f;
    const float HEARTSWIDTH = 0.1667f;
    const float HEARTSHEIGHT = 1.f;

    const int PANDAFRAMES = 13;
    const int KELLYFRAMES = 10;
    const int JACKOFRAMES = 7;
    const int HEARTSFRAMES = 6;
    float animationTime = 0.f;
    float frameRate = 4.f;
    int counter = 0;
    int pandaRowCounter = 0;
    int pandaIndex = 0;

    int pandaSunscreen = 0;
    int pandaheartPumping = 0;
    int jackoEnters = 0;
    int brokenHearted = 0;

    void animateJacko(Sprite &sprite);
    void animatePanda(int index, int row, Sprite &sprite);
    void animateKelly(Sprite &sprite);
    void animateHearts(Sprite &sprite);

};

#endif //PANDAEXPRESS_STORY_ANIMATION_SYSTEM_H
