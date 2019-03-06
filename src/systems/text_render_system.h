//
// Created by Prayansh Srivastava on 2019-03-03.
//

#ifndef PANDAEXPRESS_TEXT_SYSTEM_H
#define PANDAEXPRESS_TEXT_SYSTEM_H

#include "system.h"

class TextRenderSystem : public System {
public:
    TextRenderSystem();

    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;
};

#endif //PANDAEXPRESS_TEXT_SYSTEM_H
