//
// Created by Avery Brown on 2019-04-19.
//

#ifndef PANDAEXPRESS_STORY_END_ANIMATION_SYSTEM_H
#define PANDAEXPRESS_STORY_END_ANIMATION_SYSTEM_H


#include "system.h"

class StoryEndAnimationSystem : public System {
public:
    StoryEndAnimationSystem();

    int pandaHugging = 0;

    virtual void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;

private:
    const float PANDAWIDTH = 0.333f;
    const float PANDAHEIGHT = 1.f;
    const float KELLYWIDTH = 0.125f;
    const float KELLYHEIGHT = 0.5f;
    const int KELLYSIGHS = 10;
    const int PANDAHUG = 20;
    const int PANDARUNS = 20;
    const int KELLYGETSUP = 10;


    float pandaAnimationTime = 0.f;
    float kellyAnimationTime = 0.f;
    int pandaCounter = 0;
    int kellyCounter = 0;
    int pandaIndex = 0;
    int pandaRunning = 0;
    int kellyIndex = 0;
    int kellySighing = 0;
    int kellyGetsUp = 0;
    float kellyFrameRate = 4.f;
    float pandaFrameRate = 5.f;

    void animatePanda(Sprite &sprite);
    void animateKelly(int row, Sprite &sprite);
    void resetScene();

};

#endif //PANDAEXPRESS_STORY_END_ANIMATION_SYSTEM_H
