//
// Created by Avery Brown on 2019-03-31.
//

#ifndef PANDAEXPRESS_PAUSE_MENU_TRANSFORM_SYSTEM_H
#define PANDAEXPRESS_PAUSE_MENU_TRANSFORM_SYSTEM_H


class PauseMenuTransformSystem : public System {
private:

public:
    PauseMenuTransformSystem();

    virtual void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;
};

#endif //PANDAEXPRESS_PAUSE_MENU_TRANSFORM_SYSTEM_H
