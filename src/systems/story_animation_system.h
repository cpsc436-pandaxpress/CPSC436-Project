//
// Created by Avery Brown on 2019-04-10.
//

#ifndef PANDAEXPRESS_STORY_ANIMATION_SYSTEM_H
#define PANDAEXPRESS_STORY_ANIMATION_SYSTEM_H


#include "system.h"

class StoryAnimationSystem : public System {
public:
    StoryAnimationSystem();

    bool jackoGrabsKelly = false;

    virtual void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;

private:
    const float PANDAWIDTH = 0.07692;
    const float PANDAHEIGHT = 0.25f;
    const float KELLYWIDTH = 0.1f;
    const float KELLYHEIGHT = 1.f;
    const float JACKOWIDTH = 0.125f;
    const float JACKOHEIGHT = 0.3333f;
    const float HEARTSWIDTH = 0.1667f;
    const float HEARTSHEIGHT = 1.f;
    const float FRAMERATE = 3.f;
    const float JACKOSPEED = 160.f;
    const int PANDAFRAMES = 13;
    const int KELLYFRAMES = 10;
    const int JACKOFRAMES = 8;
    const int HEARTSFRAMES = 6;
    const int PANDASUNCREENRUBS = 27;
    const int PANDAHEARTPUMPS = 25;
    const int JACKOENTERING = 25;


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

#endif //PANDAEXPRESS_STORY_ANIMATION_SYSTEM_H
