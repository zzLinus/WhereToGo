#pragma once
#include "types.hpp"
#include <raylib.h>
#include <vector>

class Renderer {
public:
    Renderer();
    virtual ~Renderer();
    void add_renderObj(RenderObject* renderObj);
    void Render(void);
    void clear(void);

private:
public:
private:
    std::vector<RenderObject> renderObjs;
};
