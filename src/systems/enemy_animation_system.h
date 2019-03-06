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
    float breadWidth = 0.143;
    float breadHeight = 0.5;
    float llamaWidth = 0.0714;
    float llamaHeight = 0.25;
    float ghostWidth = 0.1428;
    float ghostHeight = 1.f;
    float jackoWidth = 0.143f;
    float jackoHeight = 0.25f;
    float spitWidth = 0.5f;
    float spitHeight = 0.5f;

    int breadFrames = 7;
    int llamaFrames = 14;
    int spitFrames = 2;
    int ghostFrames = 7;
    int jackoFrames = 7;
    float animationTime = 0.f;
    float frameRate = 4.f;

    void animateBread(bool alive, Sprite &sprite);
    void animateLlama(bool alive, float time, float targetTime, Sprite &sprite);
    void animateJacko(bool alive, bool evading, Sprite &sprite);
    void animateGhost(Sprite &sprite);
    void animateSpit(Sprite &sprite);




};

#endif //PANDAEXPRESS_ENEMY_ANIMATION_SYSTEM_H

