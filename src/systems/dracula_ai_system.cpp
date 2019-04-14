//
// Created by Kenneth William on 2019-02-24.
//

#include "dracula_ai_system.h"
#include <iostream>
using namespace std;

/***
 * Creating classes for each node of the behaviour tree
 */



/***
 * Checks whether Jacko has more than one health point left
 * run() returns false if healthpoints are more than one or if childnodes all return false
 */
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

/***
 * Check if the panda is dead, right now it just resets
 * but in the future we may want the boss to laugh at the
 * player when they lose
 */
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

/***
 * This node makes sure that Jacko starts chasing the Panda again if he's not
 * looking for food and always returns false
 */

class ChasePanda: public Node{
private:
    Blackboard& blackboard;
    entt::DefaultRegistry& registry;
public:
    ChasePanda(Blackboard& blackboard, entt::DefaultRegistry& registry) :
        blackboard(blackboard),
        registry(registry){}
    virtual bool run() override {
        auto drac_view = registry.view<Dracula, Chases>();
        for (auto drac_entity: drac_view) {
            auto &chase = drac_view.get<Chases>(drac_entity);

            auto panda_view = registry.view<Panda>();
            for(auto panda_entity:panda_view){
                chase.target=panda_entity;
            }

        }

        return false;
    }
};

class StompPanda: public Node{
private:
    Blackboard& blackboard;
    entt::DefaultRegistry& registry;
public:
    StompPanda(Blackboard& blackboard, entt::DefaultRegistry& registry) :
            blackboard(blackboard),
            registry(registry){}
    virtual bool run() override {
        auto drac_view = registry.view<Dracula, Transform, Velocity, Interactable, Chases>();
        for (auto drac_entity: drac_view) {
            auto &drac_transform = drac_view.get<Transform>(drac_entity);
            auto &drac_velocity = drac_view.get<Velocity>(drac_entity);
            auto &drac_chases = drac_view.get<Chases>(drac_entity);
            auto &drac_interactable = drac_view.get<Interactable>(drac_entity);

            auto panda_view = registry.view<Panda, Transform>();
            for(auto panda_entity:panda_view){
                auto &pa_transform = panda_view.get<Transform>(panda_entity);
                if(pa_transform.x > drac_transform.x && pa_transform.x < drac_transform.x+100 && pa_transform.y > drac_transform.y){
                    drac_chases.stomping=true;
                }
            }

        }

        return false;
    }
};

/***
 * This node makes Jacko try to get food when his health is low,
 * if there is no food left he will speed up to try to kill the panda
 */
class ChaseFood: public Node{
private:
    Blackboard& blackboard;
    entt::DefaultRegistry& registry;
public:
    ChaseFood(Blackboard& blackboard, entt::DefaultRegistry& registry) :
            blackboard(blackboard),
            registry(registry){}
    virtual bool run() override {
        auto drac_view = registry.view<Dracula, Chases>();
        for (auto drac_entity: drac_view) {
            auto &chase = drac_view.get<Chases>(drac_entity);

            auto food_view = registry.view<Food>();
            if (food_view.empty()){
                auto panda_view = registry.view<Panda>();
                for(auto panda_entity: panda_view){
                    chase.target=panda_entity;
                }
                chase.chase_speed=180;
            }
            for(auto food_entity:food_view){
                if(!registry.get<Food>(food_entity).eaten){
                    chase.target=food_entity;
                }
            }
        }
        return true;
    }
};

/***
 * Making these nodes global variables so they can be accessed from the update function
 */
CheckHealth* checkHealth;
CheckPandaDeath* checkPandaDeath;

DraculaAISystem::DraculaAISystem(Blackboard& blackboard, entt::DefaultRegistry& registry) {
    // Declare nodes
    root = SelectorNode();
    SelectorNode* firstSelector = new SelectorNode;
    checkPandaDeath = new CheckPandaDeath(getPandaHealth(blackboard,registry));
    checkHealth = new CheckHealth(getDraculaHealth(blackboard,registry));
    ChasePanda* chasePanda = new ChasePanda(blackboard, registry);
    ChaseFood* chaseFood = new ChaseFood(blackboard, registry);
    StompPanda* stompPanda = new StompPanda(blackboard, registry);



    // Building the behaviour tree
    root.addChild(firstSelector);

    firstSelector->addChild(checkPandaDeath);
    firstSelector->addChild(checkHealth);
    firstSelector->addChild(chasePanda);
    firstSelector->addChild(stompPanda);

    checkHealth->addChild(chaseFood);

}

void DraculaAISystem::update(Blackboard& blackboard, entt::DefaultRegistry& registry){
    checkHealth->updateHealth(getDraculaHealth(blackboard,registry));
    checkPandaDeath->updateHealth(getPandaHealth(blackboard,registry));
    root.run();
}

int DraculaAISystem::getPandaHealth(Blackboard& blackboard, entt::DefaultRegistry& registry){
    auto panda_view = registry.view<Panda, Health>();
    for(auto panda_entity : panda_view){
        auto &health = panda_view.get<Health>(panda_entity);
        return health.health_points;
    }
    return 0;
}

int DraculaAISystem::getDraculaHealth(Blackboard& blackboard, entt::DefaultRegistry& registry){
    auto drac_view = registry.view<Dracula, Health>();
    for(auto drac_entity : drac_view){
        auto &health = drac_view.get<Health>(drac_entity);
        return health.health_points;
    }
    return 0;
}

