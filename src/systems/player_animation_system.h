//
// Created by Avery Brown on 2019-02-25.
//

#ifndef PANDAEXPRESS_PLAYER_ANIMATION_SYSTEM_H
#define PANDAEXPRESS_PLAYER_ANIMATION_SYSTEM_H

#include "system.h"
#include "components/interactable.h"
#include "components/panda.h"
#include "components/transform.h"
#include "scene/scene.h"


class PlayerAnimationSystem : public System {
public:
    PlayerAnimationSystem(SceneID scene_id);

    virtual void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;


private:
    float pandawidth = 0.1;
    float pandaheight = 0.333;
    SceneID scene_id;


    float animationTime = 0.f;
    bool direction_left = false;
    int death_index = 0;



    void animate(bool alive, int frames, int index, int row, Sprite &sprite);

    void update_horizontal_scene(Blackboard &blackboard, Interactable &walkable, Sprite &sprite, Panda &panda);
    void update_vertical_boss_scene(Blackboard &blackboard, Interactable &walkable, Sprite &sprite, Panda &panda, Transform &transform);



};

#endif //PANDAEXPRESS_PLAYER_ANIMATION_SYSTEM_H
