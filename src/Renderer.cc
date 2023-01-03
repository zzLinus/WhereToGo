#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer() { }
Renderer::~Renderer() { }

void Renderer::add_renderObj(RenderObject* renderObj) { renderObjs.push_back(*renderObj); }

void Renderer::Render(void)
{
    for (auto& rdobj : renderObjs) {
        switch (rdobj.rdt) {
        case TEXTURE:
            DrawTexture(rdobj.m_texture, (int)rdobj.source.x, (int)rdobj.source.y, rdobj.color);
        case RECTLINE:
            DrawRectangleLines(
                rdobj.source.x, rdobj.source.y, rdobj.source.width, rdobj.source.height, rdobj.color);
        case TEXT:
            DrawText(
                rdobj.text, (int)rdobj.source.x, (int)rdobj.source.y, (int)rdobj.source.width, rdobj.color);
        default:;
        }
    }
    clear();
}

void Renderer::clear() { renderObjs.clear(); }
