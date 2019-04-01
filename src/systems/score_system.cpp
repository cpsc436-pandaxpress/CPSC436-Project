//
// Created by Prayansh Srivastava on 2019-03-05.
//

#include <components/score.h>
#include <graphics/text.h>
#include <components/transform.h>
#include <sstream>
#include "score_system.h"
#include "util/constants.h"

ScoreSystem::ScoreSystem(SceneType scene_type) : scene_type(scene_type) {

}

void ScoreSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    auto view = registry.view<Score, Text, Transform>();
    for (auto entity: view) {
        auto &text = view.get<Text>(entity);
        auto &transform = view.get<Transform>(entity);
        auto cam = blackboard.camera;
        switch (scene_type) {
            case JUNGLE_TYPE: {
                std::string score_text;
                std::stringstream ss;
//                ss << "SCORE: ";
                ss << (int) cam.position().x / 50;
                score_text = ss.str();
                text.set_text(score_text);
                transform.x = cam.position().x - cam.size().x / 2 + X_OFFSET;
                transform.y = cam.position().y - cam.size().y / 2 + Y_OFFSET;
            }
                break;
            case SKY_TYPE: {
                std::string score_text;
                std::stringstream ss;
//                ss << "SCORE: ";
                ss << (int) abs(cam.position().y) / 50;
                score_text = ss.str();
                text.set_text(score_text);
                transform.x = cam.position().x + cam.size().x / 2 - X_OFFSET * 3;
                transform.y = cam.position().y + cam.size().y / 2 - Y_OFFSET;
            }
                break;
            case BOSS_TYPE: {

            }
                break;
            default:
                fprintf(stderr, "Invalid scene ID: %d\n", scene_type);
        }
    }

}
