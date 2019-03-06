//
// Created by Prayansh Srivastava on 2019-03-05.
//

#ifndef PANDAEXPRESS_SCORE_SYSTEM_H
#define PANDAEXPRESS_SCORE_SYSTEM_H

#include "system.h"

class ScoreSystem : public System {
public:
    const float X_OFFSET = 100.f;
    const float Y_OFFSET = 50.f;
    ScoreSystem();

    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;
};


#endif //PANDAEXPRESS_SCORE_SYSTEM_H
