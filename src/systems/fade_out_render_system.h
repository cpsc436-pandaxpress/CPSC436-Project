//
// Created by Avery Brown on 2019-03-29.
//

#ifndef PANDAEXPRESS_FADE_OUT_REVER_H
#define PANDAEXPRESS_FADE_OUT_REVER_H

#include "system.h"

class FadeOutRenderSystem : public System {
public:
    FadeOutRenderSystem();

    virtual void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;
};


#endif //PANDAEXPRESS_FADE_OUT_REVER_H

