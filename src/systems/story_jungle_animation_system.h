//
// Created by Avery Brown on 2019-04-13.
//

#ifndef PANDAEXPRESS_STORY_JUNGLE_ANIMATION_SYSTEM_H
#define PANDAEXPRESS_STORY_JUNGLE_ANIMATION_SYSTEM_H

#include "system.h"

class StoryJungleAnimationSystem : public System {
public:
    StoryJungleAnimationSystem();

    bool jackoGrabsKelly = false;

    virtual void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;

private:
    const float PANDAWIDTH = 0.07692;
    const float PANDAHEIGHT = 0.25f;
    const float KELLYWIDTH = 0.25f;
    const float KELLYHEIGHT = 1.f;
    const float FRAMERATE = 3.f;
    const int PANDAFRAMES = 13;
    const int KELLYFRAMES = 4;

    float animationTime = 0.f;
    int counter = 0;
    int pandaIndex = 0;
    int jackoIndex = 0;
    int pandaSunscreen = 0;
    int pandaHeartPumping = 0;
    int jackoEnters = 0;
    int brokenHearted = 0;

    void animateJacko(int index, Sprite &sprite);
    void animatePanda(int index, int row, Sprite &sprite);
    void animateKelly(Sprite &sprite);
    void animateHearts(Sprite &sprite);
    void resetScene();

};

#endif //PANDAEXPRESS_STORY_JUNGLE_ANIMATION_SYSTEM_H
