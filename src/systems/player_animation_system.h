//
// Created by Avery Brown on 2019-02-25.
//

#ifndef PANDAEXPRESS_PLAYER_ANIMATION_SYSTEM_H
#define PANDAEXPRESS_PLAYER_ANIMATION_SYSTEM_H

#include "system.h"
#include "components/panda.h"
#include "components/interactable.h"
#include "scene/scene.h"


class PlayerAnimationSystem : public System {
public:
    PlayerAnimationSystem(SceneID scene_id);

    virtual void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;
    void animate(int frames, int row, Sprite &sprite);

    void update_horizontal_scene(Blackboard &blackboard, Interactable &walkable, Sprite &sprite);
    void update_vertical_boss_scene(Blackboard &blackboard, Interactable &walkable, Sprite &sprite);


private:
    float pandawidth = 0.125;
    float pandaheight = 0.2475;
    SceneID scene_id;


    float animationTime = 0.f;
    bool direction_left = false;




};

#endif //PANDAEXPRESS_PLAYER_ANIMATION_SYSTEM_H
