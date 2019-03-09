//
// Created by Prayansh Srivastava on 2019-03-05.
//

#ifndef PANDAEXPRESS_TEXT_TRANSFORM_SYSTEM_H
#define PANDAEXPRESS_TEXT_TRANSFORM_SYSTEM_H


#include "system.h"

class TextTransformSystem : public System {
public:
    TextTransformSystem();
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;
};


#endif //PANDAEXPRESS_TEXT_TRANSFORM_SYSTEM_H
