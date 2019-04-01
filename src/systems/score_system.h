//
// Created by Prayansh Srivastava on 2019-03-05.
//

#ifndef PANDAEXPRESS_SCORE_SYSTEM_H
#define PANDAEXPRESS_SCORE_SYSTEM_H

#include "system.h"
#include "scene/scene.h"

class ScoreSystem : public System {
private:
    SceneType scene_type;
public:
    const float X_OFFSET = 100.f;
    const float Y_OFFSET = 50.f;
    ScoreSystem(SceneType scene_type);

    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;
};


#endif //PANDAEXPRESS_SCORE_SYSTEM_H
