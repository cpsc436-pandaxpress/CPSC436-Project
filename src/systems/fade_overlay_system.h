//
// Created by Avery Brown on 2019-03-30.
//

#ifndef PANDAEXPRESS_FADE_OVERLAY_SYSTEM_H
#define PANDAEXPRESS_FADE_OVERLAY_SYSTEM_H

#include "system.h"


class FadeOverlaySystem : public System {
private:
    const float FADE_OUT_SPEED = 0.3;
    const float FADE_OUT_SPEED_TRANSITION = 1.0;

public:
    FadeOverlaySystem();
    virtual void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;
};

#endif //PANDAEXPRESS_FADE_OVERLAY_SYSTEM_H
