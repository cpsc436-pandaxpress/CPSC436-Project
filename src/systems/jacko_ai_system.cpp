//
// Created by Kenneth William on 2019-02-24.
//

#include "jacko_ai_system.h"
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

class StompPanda: public Node{
private:
    Blackboard& blackboard;
    entt::DefaultRegistry& registry;
public:
    StompPanda(Blackboard& blackboard, entt::DefaultRegistry& registry) :
            blackboard(blackboard),
            registry(registry){}
    virtual bool run() override {
        auto jacko_view = registry.view<Jacko, Transform, Velocity, Interactable, Chases>();
        for (auto jacko_entity: jacko_view) {
            auto &ja_transform = jacko_view.get<Transform>(jacko_entity);
            auto &ja_velocity = jacko_view.get<Velocity>(jacko_entity);
            auto &ja_chases = jacko_view.get<Chases>(jacko_entity);
            auto &ja_interactable = jacko_view.get<Interactable>(jacko_entity);

            auto panda_view = registry.view<Panda, Transform>();
            for(auto panda_entity:panda_view){
                auto &pa_transform = panda_view.get<Transform>(panda_entity);
                if(pa_transform.x > ja_transform.x && pa_transform.x < ja_transform.x+100 && pa_transform.y > ja_transform.y){
                    ja_chases.stomping=true;
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
        auto jacko_view = registry.view<Jacko, Chases>();
        for (auto jacko_entity: jacko_view) {
            auto &chase = jacko_view.get<Chases>(jacko_entity);

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

JackoAISystem::JackoAISystem(Blackboard& blackboard, entt::DefaultRegistry& registry) {
    // Declare nodes
    root = new SelectorNode;
    SelectorNode* firstSelector = new SelectorNode;
    checkPandaDeath = new CheckPandaDeath(getPandaHealth(blackboard,registry));
    checkHealth = new CheckHealth(getJackoHealth(blackboard,registry));
    ChasePanda* chasePanda = new ChasePanda(blackboard, registry);
    ChaseFood* chaseFood = new ChaseFood(blackboard, registry);
    StompPanda* stompPanda = new StompPanda(blackboard, registry);



    // Building the behaviour tree
    root->addChild(firstSelector);

    firstSelector->addChild(checkPandaDeath);
    firstSelector->addChild(checkHealth);
    firstSelector->addChild(chasePanda);
    firstSelector->addChild(stompPanda);

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
        return health.health_points;
    }
    return 0;
}
/*
int JackoAISystem::getPandaXLocation(Blackboard& blackboard, entt::DefaultRegistry& registry){
    auto panda_view = registry.view<Panda, Transform>();
    for(auto panda_entity : panda_view){
        auto &transform = panda_view.get<Transform>(panda_entity);
        return transform.x;
    }
    return 0;
}
int JackoAISystem::getPandaYLocation(Blackboard& blackboard, entt::DefaultRegistry& registry){
    auto panda_view = registry.view<Panda, Transform>();
    for(auto panda_entity : panda_view){
        auto &transform = panda_view.get<Transform>(panda_entity);
        return transform.y;
    }
    return 0;
}

int JackoAISystem::getPandaXGridLocation(int x){

}
int JackoAISystem::getPandaYGridLocation(int y){

}
*/
int JackoAISystem::getJackoHealth(Blackboard& blackboard, entt::DefaultRegistry& registry){
    auto jacko_view = registry.view<Jacko, Health>();
    for(auto jacko_entity : jacko_view){
        auto &health = jacko_view.get<Health>(jacko_entity);
        return health.health_points;
    }
    return 0;
}

