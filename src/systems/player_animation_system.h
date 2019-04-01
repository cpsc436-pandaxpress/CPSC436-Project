//
// Created by Avery Brown on 2019-02-25.
//

#ifndef PANDAEXPRESS_PLAYER_ANIMATION_SYSTEM_H
#define PANDAEXPRESS_PLAYER_ANIMATION_SYSTEM_H

#include "system.h"
#include "components/interactable.h"
#include "scene/scene.h"


class PlayerAnimationSystem : public System {
public:
    PlayerAnimationSystem(SceneType scene_type);

    virtual void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;


private:
    float pandawidth = 0.1;
    float pandaheight = 0.25;
    SceneType scene_type;


    float animationTime = 0.f;
    bool direction_left = false;


    void animate(int frames, int index, int row, Sprite &sprite);

    void update_horizontal_scene(Blackboard &blackboard, Interactable &walkable, Sprite &sprite);
    void update_vertical_boss_scene(Blackboard &blackboard, Interactable &walkable, Sprite &sprite);



};

#endif //PANDAEXPRESS_PLAYER_ANIMATION_SYSTEM_H
