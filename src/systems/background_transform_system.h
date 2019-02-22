//
// Created by Prayansh Srivastava on 2019-02-07.
//

#ifndef PANDAEXPRESS_BACKGROUND_TRANSFORM_SYSTEM_H
#define PANDAEXPRESS_BACKGROUND_TRANSFORM_SYSTEM_H




#include "system.h"

class BackgroundTransformSystem: public System {
public:
    const float LAYER_SPEED = 37.5f;
    BackgroundTransformSystem();

    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;
};


#endif //PANDAEXPRESS_BACKGROUND_TRANSFORM_SYSTEM_H
