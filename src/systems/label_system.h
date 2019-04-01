//
// Created by Prayansh Srivastava on 2019-03-30.
//

#ifndef PANDAEXPRESS_LABEL_SYSTEM_H
#define PANDAEXPRESS_LABEL_SYSTEM_H


#include "system.h"

class LabelSystem : public System {
public:
    LabelSystem();
    void update(Blackboard &blackboard, entt::DefaultRegistry &registry);
};


#endif //PANDAEXPRESS_LABEL_SYSTEM_H
