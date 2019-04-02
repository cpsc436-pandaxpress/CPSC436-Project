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
 * Checks whether Dracula has more than one health point left
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
 * This node makes sure that Dracula starts chasing the Panda again if he's not
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
        auto dracula_view = registry.view<Dracula, Chases>();
        for (auto dracula_entity: dracula_view) {
            auto &chase = dracula_view.get<Chases>(dracula_entity);

            auto panda_view = registry.view<Panda>();
            for(auto panda_entity:panda_view){
                chase.target=panda_entity;
            }

        }

        return false;
    }
};

/***
 * This node makes Dracula try to get food when his health is low,
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
        auto dracula_view = registry.view<Dracula, Chases>();
        for (auto dracula_entity: dracula_view) {
            auto &chase = dracula_view.get<Chases>(dracula_entity);

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
CheckHealth* checkDraculaHealth;
CheckPandaDeath* checkPandaDead;


DraculaAISystem::DraculaAISystem(Blackboard& blackboard, entt::DefaultRegistry& registry, AStarSystem& a_star_system) {
    // Declare nodes
    root = new SelectorNode;
    SelectorNode* firstSelector = new SelectorNode;
    checkPandaDead = new CheckPandaDeath(getPandaHealth(blackboard,registry));
    checkDraculaHealth = new CheckHealth(getDraculaHealth(blackboard,registry));
    ChasePanda* chasePanda = new ChasePanda(blackboard, registry);
    ChaseFood* chaseFood = new ChaseFood(blackboard, registry);




    // Building the behaviour tree
    root->addChild(firstSelector);

    firstSelector->addChild(checkPandaDead);
    firstSelector->addChild(checkDraculaHealth);
    firstSelector->addChild(chasePanda);


    checkDraculaHealth->addChild(chaseFood);

}

void DraculaAISystem::update(Blackboard& blackboard, entt::DefaultRegistry& registry){
    checkDraculaHealth->updateHealth(getDraculaHealth(blackboard,registry));
    checkPandaDead->updateHealth(getPandaHealth(blackboard,registry));
    root->run();
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
    auto dracula_view = registry.view<Dracula, Health>();
    for(auto dracula_entity : dracula_view){
        auto &health = dracula_view.get<Health>(dracula_entity);
        return health.health_points;
    }
    return 0;
}

void DraculaAISystem::ShootBats(Blackboard& blackboard, entt::DefaultRegistry& registry, AStarSystem& a_star_system){
    std::vector<Coordinates*> path = a_star_system.getProjectilePath(blackboard, registry);
    int bat_entity = registry.create();
    auto texture = blackboard.texture_manager.get_texture("bat");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    float scaleY = 50.0 / texture.height();
    float scaleX = 50.0 / texture.width();
    registry.assign<Transform>(bat_entity, path[0]->x, path[0]->y, 0., scaleX, scaleY);
    registry.assign<Sprite>(bat_entity, texture, shader, mesh);
    registry.assign<Velocity>(bat_entity);
    registry.assign<Timer>(bat_entity);
    registry.assign<Collidable>(bat_entity, texture.width() * scaleX,
                                 texture.height() * scaleY);
    registry.assign<Seeks>(bat_entity, path);

}
