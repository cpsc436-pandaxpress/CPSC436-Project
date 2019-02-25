//
// Created by Kenneth William on 2019-02-24.
//

#include "jacko_ai_system.h"
#include <iostream>
using namespace std;



class CheckHealth: public SelectorNode{
private:
    int health;

public:
    CheckHealth(int health) :
            health(health) {}

    void updateHealth(int newHealth){
        health=newHealth;
    }
    virtual bool run() override {
        if(health>=2){
            return false;
        }
        for (Node* child : getChildren()) {
            if (child->run())
                return true;
        }
        return false;
    }
};

class CheckPandaDeath: public Node{
private:
    int health;

public:
    CheckPandaDeath(int health) :
            health(health) {}
    void updateHealth(int newHealth){
        health=newHealth;
    }
    virtual bool run() override {
        return (health<1);
    }
};

class ChasePanda: public Node{
private:
    Blackboard& blackboard;
    entt::DefaultRegistry& registry;
public:
    ChasePanda(Blackboard& blackboard, entt::DefaultRegistry& registry) :
        blackboard(blackboard),
        registry(registry){}
    virtual bool run() override {
        auto jacko_view = registry.view<Jacko, Chases>();
        for (auto jacko_entity: jacko_view) {
            auto &chase = jacko_view.get<Chases>(jacko_entity);

            auto panda_view = registry.view<Panda>();
            for(auto panda_entity:panda_view){
                chase.target=panda_entity;
            }

        }

        return false;
    }
};

class ChaseFood: public Node{
private:
    Blackboard& blackboard;
    entt::DefaultRegistry& registry;
public:
    ChaseFood(Blackboard& blackboard, entt::DefaultRegistry& registry) :
            blackboard(blackboard),
            registry(registry){}
    virtual bool run() override {
        auto jacko_view = registry.view<Jacko, Chases>();
        for (auto jacko_entity: jacko_view) {
            auto &chase = jacko_view.get<Chases>(jacko_entity);

            auto food_view = registry.view<Food>();
            for(auto food_entity:food_view){
                if(!registry.get<Food>(food_entity).eaten){
                    chase.target=food_entity;
                }

            }

        }

        return true;
    }
};

CheckHealth* checkHealth;
CheckPandaDeath* checkPandaDeath;

JackoAISystem::JackoAISystem(Blackboard& blackboard, entt::DefaultRegistry& registry) {
    // Declare nodes
    root = new SelectorNode;
    SelectorNode* firstSelector = new SelectorNode;
    checkPandaDeath = new CheckPandaDeath(getPandaHealth(blackboard,registry));
    checkHealth = new CheckHealth(getJackoHealth(blackboard,registry));
    ChasePanda* chasePanda = new ChasePanda(blackboard, registry);
    ChaseFood* chaseFood = new ChaseFood(blackboard, registry);



    // Build the tree
    root->addChild(firstSelector);

    firstSelector->addChild(checkPandaDeath);
    firstSelector->addChild(checkHealth);
    firstSelector->addChild(chasePanda);

    checkHealth->addChild(chaseFood);

}

void JackoAISystem::update(Blackboard& blackboard, entt::DefaultRegistry& registry){
    checkHealth->updateHealth(getJackoHealth(blackboard,registry));
    checkPandaDeath->updateHealth(getPandaHealth(blackboard,registry));
    root->run();
}

int JackoAISystem::getPandaHealth(Blackboard& blackboard, entt::DefaultRegistry& registry){
    auto panda_view = registry.view<Panda, Health>();
    for(auto panda_entity : panda_view){
        auto &health = panda_view.get<Health>(panda_entity);
        return health.healthPoints;
    }
    return 0;
}

int JackoAISystem::getJackoHealth(Blackboard& blackboard, entt::DefaultRegistry& registry){
    auto jacko_view = registry.view<Jacko, Health>();
    for(auto jacko_entity : jacko_view){
        auto &health = jacko_view.get<Health>(jacko_entity);
        return health.healthPoints;
    }
    return 0;
}