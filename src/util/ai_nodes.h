//
// Created by Kenneth William on 2019-04-14.
//

#ifndef PANDAEXPRESS_AI_NODES_H
#define PANDAEXPRESS_AI_NODES_H

#include "systems/system.h"
#include "systems/a_star_system.h"
#include "util/selector_node.h"
#include "util/coordinates.h"
#include "util/Location.h"
#include "components/dracula.h"
#include "components/boss.h"
#include "components/chases.h"
#include "components/seeks.h"
#include "components/evades.h"
#include "components/timer.h"
#include "components/panda.h"
#include "components/food.h"
#include "components/transform.h"
#include "components/velocity.h"
#include "components/interactable.h"
#include "components/health.h"

class AINodes {
public:

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
            auto drac_view = registry.view<Boss, Chases>();
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
            auto drac_view = registry.view<Boss, Transform, Velocity, Interactable, Chases>();
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

    class ShootBat: public Node{
    private:
        Blackboard& blackboard;
        entt::DefaultRegistry& registry;
        AStarSystem& a_star_system;
        int batCount = 0;
        bool pathSet = false;
        std::vector<Coordinates *> path;
    public:
        ShootBat(Blackboard& blackboard, entt::DefaultRegistry& registry, AStarSystem& a_star_system) :
                blackboard(blackboard),
                registry(registry),
                a_star_system(a_star_system){}
        virtual bool run() override {
            auto drac_view = registry.view<Boss, Transform, Chases, Velocity, Timer>();
            for (auto drac_entity: drac_view) {
                auto &drac_transform = drac_view.get<Transform>(drac_entity);
                auto &drac_velocity = drac_view.get<Velocity>(drac_entity);
                auto &drac_chases = drac_view.get<Chases>(drac_entity);
                auto &timer = drac_view.get<Timer>(drac_entity);

                if(timer.watch_exists("batAttack")) {
                    if (timer.is_done("batAttack")) {
                        if(!pathSet){
                            path = a_star_system.getProjectilePath(blackboard,registry);
                            pathSet=true;
                        }
                        drac_chases.chase_speed=0.f;
                        drac_velocity.x_velocity = 0;
                        drac_velocity.y_velocity = 0;

                        if (timer.watch_exists("batShooter")) {

                            if (timer.is_done("batShooter")) {
                                if(batCount <8){
                                    auto panda_view = registry.view<Panda, Transform>();
                                    for (auto panda_entity:panda_view) {
                                        auto &pa_transform = panda_view.get<Transform>(panda_entity);


                                        uint32_t bat_entity = registry.create();

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
                                        batCount++;
                                        timer.save_watch("batShooter", 0.1f);
                                }

                                }else{
                                    timer.save_watch("batAttack", 4.f);
                                    drac_chases.chase_speed=120.f;
                                    batCount=0;
                                    pathSet=false;
                                    return false;
                                }

                            }
                        } else {
                            timer.save_watch("batShooter", 1.f);

                        }
                    }
                }else {
                    timer.save_watch("batAttack", 4.f);
                    return false;
                }

            }

            return false;
        }
    };


    class TeleportAttack: public Node{
    private:
        Blackboard& blackboard;
        entt::DefaultRegistry& registry;
        AStarSystem& a_star_system;
        bool pathSet = false;
        std::vector<Coordinates *> path;
    public:
        TeleportAttack(Blackboard& blackboard, entt::DefaultRegistry& registry, AStarSystem& a_star_system):
                blackboard(blackboard),
                registry(registry),
                a_star_system(a_star_system){}
            virtual bool run() override {
                    auto drac_view = registry.view<Boss, Transform, Chases, Velocity, Timer>();
                    for (auto drac_entity: drac_view) {
                        auto &drac_transform = drac_view.get<Transform>(drac_entity);
                        auto &drac_velocity = drac_view.get<Velocity>(drac_entity);
                        auto &drac_chases = drac_view.get<Chases>(drac_entity);
                        auto &timer = drac_view.get<Timer>(drac_entity);

                        if(timer.watch_exists("teleport")) {
                            if (timer.is_done("teleport")) {
                                if(timer.watch_exists("teleportDelay")) {
                                    drac_chases.chase_speed=0.f;
                                    drac_velocity.x_velocity=0.f;
                                    drac_velocity.y_velocity=0.f;

                                    if (timer.is_done("teleportDelay")) {
                                        auto panda_view = registry.view<Panda, Transform>();
                                        for(auto panda_entity: panda_view) {
                                            auto panda_transform = panda_view.get<Transform>(panda_entity);

                                            Location *panda_location = a_star_system.getGridLocation(panda_transform.x, panda_transform.y);
                                            Location *teleport_location = new Location(panda_location->i, panda_location->j+2);


                                            Coordinates *teleport_coords = a_star_system.getScreenLocation(teleport_location->i,
                                                                                                           teleport_location->j);
                                            drac_transform.x = teleport_coords->x;
                                            drac_transform.y = teleport_coords->y;
                                            drac_chases.chase_speed=120.f;
                                            timer.remove("teleportDelay");
                                            timer.save_watch("teleport", 1.f);
                                            return true;
                                        }

                                    }else{
                                        return false;
                                    }
                                }else{
                                    timer.save_watch("teleportDelay", 0.5f);
                                    return true;
                                }

                            }

                        }else {
                            timer.save_watch("teleport", 1.f);
                            return false;
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
            auto drac_view = registry.view<Boss, Chases>();
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

};


#endif //PANDAEXPRESS_AI_NODES_H
