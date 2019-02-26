//
// Created by Avery Brown on 2019-02-25.
//

#ifndef PANDAEXPRESS_PLAYER_ANIMATION_SYSTEM_H
#define PANDAEXPRESS_PLAYER_ANIMATION_SYSTEM_H

#include "system.h"
#include "components/panda.h"
#include "scene/scene.h"


class PlayerAnimationSystem : public System {
public:
    PlayerAnimationSystem(SceneID scene_id);

    virtual void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;
    void animate(int frames, int index, Sprite &sprite);


private:
    float pandawidth = 0.1;
    float pandaheight = 1;
    SceneID scene_id;


    float animationTime = 0.f;


};

#endif //PANDAEXPRESS_PLAYER_ANIMATION_SYSTEM_H
