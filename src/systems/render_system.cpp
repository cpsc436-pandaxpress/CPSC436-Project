//
// Created by Prayansh Srivastava on 2019-04-07.
//

#include <graphics/render.h>
#include <graphics/background.h>
#include <graphics/cave.h>
#include <graphics/cave_entrance.h>
#include <graphics/text.h>
#include <graphics/fade_overlay.h>
#include <graphics/health_bar.h>
#include <components/layer.h>
#include <components/pause_menu.h>
#include "render_system.h"

struct CompareRenderable {
    bool operator()(const Renderable* left, const Renderable* right) const {
        return left->depth < right->depth;
    }
} layerComparator;


void RenderSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    updateLayers(registry);
    std::vector<Renderable *> allRenderables;
    auto viewSprites = registry.view<Sprite>();
    for (auto entity: viewSprites) {
        auto &r = viewSprites.get(entity);
        allRenderables.push_back(&r);
    }
    auto viewBackgrounds = registry.view<Background>();
    for (auto entity: viewBackgrounds) {
        auto &r = viewBackgrounds.get(entity);
        allRenderables.push_back(&r);
    }
    auto viewText = registry.view<Text>();
    for (auto entity: viewText) {
        auto &r = viewText.get(entity);
        allRenderables.push_back(&r);
    }
    auto viewCave = registry.view<Cave>();
    for (auto entity: viewCave) {
        auto &r = viewCave.get(entity);
        allRenderables.push_back(&r);
    }
    auto viewCaveEntrance = registry.view<CaveEntrance>();
    for (auto entity: viewCaveEntrance) {
        auto &r = viewCaveEntrance.get(entity);
        allRenderables.push_back(&r);
    }
    auto viewFadeOverlay = registry.view<FadeOverlay>();
    for (auto entity: viewFadeOverlay) {
        auto &r = viewFadeOverlay.get(entity);
        allRenderables.push_back(&r);
    }
    auto viewHealthBar = registry.view<HealthBar>();
    for (auto entity: viewHealthBar) {
        auto &r = viewHealthBar.get(entity);
        allRenderables.push_back(&r);
    }
    sort(allRenderables.begin(), allRenderables.end(), layerComparator);
    for (auto render : allRenderables) {
        blackboard.window.draw((Renderable *) render, blackboard.camera.get_projection());
    }
}

void RenderSystem::updateLayers(entt::DefaultRegistry &registry) {
    auto layerViews = registry.view<Layer>();
    for (auto entity:layerViews) {
        auto &layer = layerViews.get(entity);
        if (registry.has<Sprite>(entity)) {
            auto &sprite = registry.get<Sprite>(entity);
            sprite.depth = layer.layer;
        } else if (registry.has<Background>(entity)) {
            auto &background = registry.get<Background>(entity);
            background.depth = layer.layer;
        } else if (registry.has<FadeOverlay>(entity)) {
            auto &fade = registry.get<FadeOverlay>(entity);
            fade.depth = layer.layer;
        } else if (registry.has<Cave>(entity)) {
            auto &cave = registry.get<Cave>(entity);
            cave.depth = layer.layer;
        } else if (registry.has<CaveEntrance>(entity)) {
            auto &entrance = registry.get<CaveEntrance>(entity);
            entrance.depth = layer.layer;
        } else if (registry.has<Text>(entity)) {
            auto &text = registry.get<Text>(entity);
            text.depth = layer.layer;
        }
        if (registry.has<HealthBar>(entity)) {
            auto &health = registry.get<HealthBar>(entity);
            health.depth = layer.layer;
        }
    }
}
