//
// Created by Prayansh Srivastava on 2019-02-07.
//

#ifndef PANDAEXPRESS_BACKGROUND_TRANSFORM_SYSTEM_H
#define PANDAEXPRESS_BACKGROUND_TRANSFORM_SYSTEM_H

#include "system.h"
#include <scene/scene.h>
#include <graphics/background.h>

class BackgroundTransformSystem: public System {
private:
    SceneType scene_type;
    float clamp(float value, float from, float to);
public:
    const float HORIZONTAL_LAYER_SPEED = 37.5f;
    const float VERTICAL_LAYER_SPEED = 15.0f;
    const float STORY_LAYER_SPEED = 10.0f;
    const float WAVE_MAX = 20.0f;
    const float WAVE_MIN = -20.0f;


    BackgroundTransformSystem(SceneType scene_type);

    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;

    void horizontal_background_transform(Blackboard &blackboard, Background &background);

    void vertical_background_transform(Blackboard &blackboard, Background &background);

    void boss_background_transform(Blackboard &blackboard, Background &background);

    void story_beach_background_transform(Blackboard &blackboard, Background &background);

};


#endif //PANDAEXPRESS_BACKGROUND_TRANSFORM_SYSTEM_H
