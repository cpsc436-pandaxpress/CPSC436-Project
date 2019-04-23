//
// Created by Avery Brown on 2019-03-04.
//

#ifndef PANDAEXPRESS_ENEMY_ANIMATION_SYSTEM_H
#define PANDAEXPRESS_ENEMY_ANIMATION_SYSTEM_H

#include "system.h"


class EnemyAnimationSystem : public System {
public:
    EnemyAnimationSystem();

    virtual void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;

private:
    const float breadWidth = 0.143;
    const float breadHeight = 0.5;
    const float llamaWidth = 0.0714;
    const float llamaHeight = 0.25;
    const float ghostWidth = 1. / 7.;
    const float ghostHeight = 1.f;
    const float jackoWidth = 0.143f;
    const float jackoHeight = 0.25f;
    const float spitWidth = 0.5f;
    const float spitHeight = 0.5f;
    const float draculaWidth = 0.20f;
    const float draculaHeight = 0.25f;
    const float batWidth = 0.5f;
    const float batHeight = 1.f;

    const int jackoFrames = 7;
    const int spitFrames = 2;
    const int ghostFrames = 7;
    const int draculaFrames = 5;
    const int batFrames = 2;
    float animationTime = 0.f;
    float frameRate = 4.f;
    int counter = 0;
    int draculaIndex = 0;

    void animateBread(bool alive, Sprite &sprite);
    void animateLlama(bool alive, float currentTime, float targetTime, Sprite &sprite);
    void animateJacko(bool alive, bool evading, Sprite &sprite);
    void animateGhost(Sprite &sprite);
    void animateSpit(Sprite &sprite);
    void animateDracula(bool alive, bool evading, int shooterCount, Sprite &sprite);
    void animateBats(Sprite &sprite);


};

#endif //PANDAEXPRESS_ENEMY_ANIMATION_SYSTEM_H

