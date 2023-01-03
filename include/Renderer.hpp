#pragma once
#include "types.hpp"
#include <raylib.h>
#include <vector>

class Renderer {
public:
    Renderer();
    virtual ~Renderer();
    void add_renderObj(RenderObject* renderObj, renderMode rm);
    void Render_2D(void);
    void Render_NORM(void);

private:
public:
private:
    std::vector<RenderObject> renderObjs_2d;
    std::vector<RenderObject> renderObjs_norm;
};
