//
// Created by Kenneth William on 2019-03-06.
//

#include "falling_platform_system.h"


void FallingPlatformSystem::update(Blackboard& blackboard, entt::DefaultRegistry& registry) {

    auto falling_platform_view = registry.view<Platform, Transform, Timer>();
    for (auto falling_platform_entity : falling_platform_view) {

        auto& platform_timer  = falling_platform_view.get<Timer>(falling_platform_entity);
        auto& transform  = falling_platform_view.get<Transform>(falling_platform_entity);
        auto& platform  = falling_platform_view.get<Platform>(falling_platform_entity);

        if(platform.trigger){



        if(platform.shaking){
            if(platform.shakeLeft){
                transform.x-=5;
            }else{
                transform.x+=5;
            }
            platform.shakeLeft=!platform.shakeLeft;
        }

        if(platform_timer.watch_exists(FALL)){
            if(platform_timer.is_done(FALL)) {
                platform.shaking = false;
                registry.assign<ObeysGravity>(falling_platform_entity,1.4f);
                registry.remove<Timer>(falling_platform_entity);
            }
        }else{
            platform_timer.save_watch(FALL, WARNING_TIME);
        }

        }
    }
}