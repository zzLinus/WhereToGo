#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer() { }
Renderer::~Renderer() { }

void Renderer::add_renderObj(RenderObject* renderObj, renderMode rm)
{
    if (rm == RENDER_2D)
        renderObjs_2d.push_back(*renderObj);
    else if (rm == RENDER_NOR)
        renderObjs_norm.push_back(*renderObj);
}

void Renderer::Render_2D(void)
{
    for (auto& rdobj : renderObjs_2d) {
        switch (rdobj.rdt) {
        case TEXTURE:
            DrawTexture(rdobj.m_texture, (int)rdobj.m_source.x, (int)rdobj.m_source.y, rdobj.color);
        case RECTLINE:
            DrawRectangleLines(
                rdobj.m_source.x, rdobj.m_source.y, rdobj.m_source.width, rdobj.m_source.height, rdobj.color);
        case TEXT:
            DrawText(rdobj.text, (int)rdobj.m_source.x, (int)rdobj.m_source.y, (int)rdobj.m_source.width,
                rdobj.color);
        case TEXTUREPRO:
            DrawTexturePro(rdobj.m_texture, rdobj.m_source, rdobj.m_dest,
                Vector2 { rdobj.vec4.x, rdobj.vec4.x }, rdobj.vec4.z, rdobj.color);
        default:;
        }
    }
    renderObjs_2d.clear();
}

void Renderer::Render_NORM(void)
{
    for (auto& rdobj : renderObjs_norm) {
        switch (rdobj.rdt) {
        case TEXTURE:
            DrawTexture(rdobj.m_texture, (int)rdobj.m_source.x, (int)rdobj.m_source.y, rdobj.color);
        case RECTLINE:
            DrawRectangleLines(
                rdobj.m_source.x, rdobj.m_source.y, rdobj.m_source.width, rdobj.m_source.height, rdobj.color);
        case TEXT:
            DrawText(rdobj.text, (int)rdobj.m_source.x, (int)rdobj.m_source.y, (int)rdobj.m_source.width,
                rdobj.color);
        case TEXTUREPRO:
            DrawTexturePro(rdobj.m_texture, rdobj.m_source, rdobj.m_dest,
                Vector2 { rdobj.vec4.x, rdobj.vec4.x }, rdobj.vec4.z, rdobj.color);
        default:;
        }
    }
    renderObjs_norm.clear();
}
