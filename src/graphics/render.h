//
// Created by alex on 24/01/19.
//

#pragma once

#include "sprite.h"

#include "../util/gl_utils.h"

class Renderable {
public:
    virtual void draw(const mat3& projection) = 0;
};

// interface for renderables, like framebuffers or the window
class RenderTarget {
public:
    virtual void draw(Renderable& renderable, const mat3& projection) = 0;

};