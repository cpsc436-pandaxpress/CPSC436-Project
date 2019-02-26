
#include "player_animation_system.h"
#include "components/panda.h"
#include "components/interactable.h"
#include "util/constants.h"



PlayerAnimationSystem::PlayerAnimationSystem(SceneID scene_id) :
        scene_id(scene_id) {}

void PlayerAnimationSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {

    auto view = registry.view<Panda, Interactable, Sprite>();

    for (auto entity: view) {
        auto &panda = view.get<Panda>(entity);
        auto &walkable = view.get<Interactable>(entity);
        auto &sprite = view.get<Sprite>(entity);
        /*
         * Walking
         */
        int frames, index;
        float frameRate;

        if (walkable.grounded) {
            frames = 8;
            index = 0;
            animate(frames, index, sprite);
            frameRate = 0.1f;
        }

        /*
         * Jumping
         */
        if (!walkable.grounded) {
            frames = 2;
            index = 8;
            animate(frames, index, sprite);
            frameRate = 0.01f;
        }
        animationTime += frameRate;


    }
}
void PlayerAnimationSystem::animate(int frames, int index, Sprite &sprite){
    index += ((int) animationTime % frames);
    vec2 uv1 = {index*pandawidth, index*pandaheight};
    vec2 uv2 = {(index+1)*pandawidth, (index+1)*pandaheight};
    sprite.set_uvs(uv1, uv2);

}

