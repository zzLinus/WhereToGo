#include "Renderer.hpp"
#include <algorithm>
#include <iostream>

extern DebugInfo debugInfo;

Renderer::Renderer() { }
Renderer::~Renderer() { }

void Renderer::add_renderObj(RenderObject* renderObj, renderMode rm)
{
    if (rm == RENDER_2D)
        renderObjs_2d.push_back(*renderObj);
    else if (rm == RENDER_2D_MOVER)
        renderObjs_2d_mover.push_back(*renderObj);
    else if (rm == RENDER_2D_BG)
        renderObjs_2d_bg.push_back(*renderObj);
    else if (rm == RENDER_2D_COLLI)
        renderObjs_2d_colli.push_back(*renderObj);
    else if (rm == RENDER_NOR)
        renderObjs_norm.push_back(*renderObj);
}

void Renderer::Render_2D(void)
{
    std::sort(renderObjs_2d.begin(), renderObjs_2d.end(),
        [](const RenderObject& lhs, const RenderObject& rhs) { return lhs.y < rhs.y; });
    for (auto& rdobj : renderObjs_2d) {
        switch (rdobj.rdt) {
        case TEXTURE: {
            Render_2D_mover(rdobj.y);
            DrawTexture(rdobj.m_texture, (int)rdobj.m_source.x, (int)rdobj.m_source.y, rdobj.color);
#ifdef DEBUG
            if ((bool)debugInfo)
                DrawLine(rdobj.m_source.x, rdobj.y, rdobj.m_source.x + 10, rdobj.y, RED);
#endif
            break;
        }
        case RECTLINE: {
            Render_2D_mover(rdobj.y);
            DrawRectangleLines(
                rdobj.m_source.x, rdobj.m_source.y, rdobj.m_source.width, rdobj.m_source.height, rdobj.color);
#ifdef DEBUG
            if ((bool)debugInfo)
                DrawLine(rdobj.m_source.x, rdobj.y, rdobj.m_source.x + rdobj.m_source.width, rdobj.y, RED);
#endif
            break;
        }
        case TEXT: {
            Render_2D_mover(rdobj.y);
            DrawText(rdobj.text, (int)rdobj.m_source.x, (int)rdobj.m_source.y, (int)rdobj.m_source.width,
                rdobj.color);
#ifdef DEBUG
            if ((bool)debugInfo)
                DrawLine(rdobj.m_source.x, rdobj.y, rdobj.m_source.x + rdobj.m_source.width, rdobj.y, RED);
#endif
            break;
        }
        case TEXTUREPRO: {
            Render_2D_mover(rdobj.y);
            DrawTexturePro(rdobj.m_texture, rdobj.m_source, rdobj.m_dest,
                Vector2 { rdobj.vec4.x, rdobj.vec4.x }, rdobj.vec4.z, rdobj.color);
#ifdef DEBUG
            if ((bool)debugInfo)
                DrawLine(rdobj.m_dest.x, rdobj.y, rdobj.m_dest.x + rdobj.m_dest.width, rdobj.y, RED);
#endif
            break;
        }
        case TEXTURERECT: {
            Render_2D_mover(rdobj.y);
            DrawTextureRec(rdobj.m_texture, rdobj.m_source, Vector2 { .x = rdobj.vec4.x, .y = rdobj.vec4.y },
                rdobj.color);
#ifdef DEBUG
            if ((bool)debugInfo)
                DrawLine(rdobj.vec4.x, rdobj.y, rdobj.vec4.x + rdobj.m_source.width, rdobj.y, RED);
#endif
            break;
        }
        case RECTREC: {
            Render_2D_mover(rdobj.y);
            DrawRectangleRec(rdobj.m_source, rdobj.color);
#ifdef DEBUG
            if ((bool)debugInfo)
                DrawLine(rdobj.m_source.x, rdobj.y, rdobj.m_source.x + rdobj.m_source.width, rdobj.y, RED);
#endif
            break;
        }
        case RECTLINEEX: {
            Render_2D_mover(rdobj.y);
            DrawRectangleLinesEx(rdobj.m_source, rdobj.lineThick, rdobj.color);
#ifdef DEBUG
            if ((bool)debugInfo)
                DrawLine(rdobj.m_source.x, rdobj.y, rdobj.m_source.x + rdobj.m_source.width, rdobj.y, RED);
#endif
            break;
        }
        default:;
        }
    }

    if (!renderObjs_2d_mover.empty())
        Render_2D_mover((float)INT32_MAX);

    renderObjs_2d.clear();
    renderObjs_2d_mover.clear();
}

void Renderer::Render_2D_mover(float y_dest)
{
    auto it = renderObjs_2d_mover.begin();
    for (auto& rdobj : renderObjs_2d_mover) {
        switch (rdobj.rdt) {
        case TEXTUREPRO: {
            float y = rdobj.m_texture.height + rdobj.m_dest.y;
            if (y < y_dest) {
                DrawTexturePro(rdobj.m_texture, rdobj.m_source, rdobj.m_dest,
                    Vector2 { rdobj.vec4.x, rdobj.vec4.x }, rdobj.vec4.z, rdobj.color);
                renderObjs_2d_mover.erase(it);
            }
            break;
        }
        case TEXTURERECT: {
            float y = rdobj.m_texture.height + rdobj.vec4.y;
            if (y < y_dest)
                DrawTextureRec(rdobj.m_texture, rdobj.m_source,
                    Vector2 { .x = rdobj.vec4.x, .y = rdobj.vec4.y }, rdobj.color);
            break;
        }
        case RECTREC: {
            float y = rdobj.m_source.height + rdobj.m_source.y;
            if (y < y_dest)
                DrawRectangleRec(rdobj.m_source, rdobj.color);
            break;
        }
        case RECTLINEEX: {
            float y = rdobj.m_source.height + rdobj.m_source.y;
            if (y < y_dest)
                DrawRectangleLinesEx(rdobj.m_source, rdobj.lineThick, rdobj.color);
            break;
        }
        default:;
        }
        it++;
    }
}

void Renderer::Render_NORM(void)
{
    for (auto& rdobj : renderObjs_norm) {
        switch (rdobj.rdt) {
        case TEXT:
            DrawText(rdobj.text, (int)rdobj.m_source.x, (int)rdobj.m_source.y, (int)rdobj.m_source.width,
                rdobj.color);
            break;
        case TEXTURE:
            DrawTexture(rdobj.m_texture, (int)rdobj.m_source.x, (int)rdobj.m_source.y, rdobj.color);
            break;
        case RECTLINE:
            DrawRectangleLines(
                rdobj.m_source.x, rdobj.m_source.y, rdobj.m_source.width, rdobj.m_source.height, rdobj.color);
            break;
        case TEXTUREPRO:
            DrawTexturePro(rdobj.m_texture, rdobj.m_source, rdobj.m_dest,
                Vector2 { rdobj.vec4.x, rdobj.vec4.x }, rdobj.vec4.z, rdobj.color);
            break;
        case TEXTURERECT:
            break;
        case RECTREC:
            break;
        case RECTLINEEX:
            break;
        default:;
        }
    }
    renderObjs_norm.clear();
}

void Renderer::Render_2D_bg()
{
    for (auto& rdobj : renderObjs_2d_bg) {
        switch (rdobj.rdt) {
        case TEXT:
            DrawText(rdobj.text, (int)rdobj.m_source.x, (int)rdobj.m_source.y, (int)rdobj.m_source.width,
                rdobj.color);
            break;
        case TEXTURE:
            DrawTexture(rdobj.m_texture, (int)rdobj.m_source.x, (int)rdobj.m_source.y, rdobj.color);
            break;
        case RECTLINE:
            DrawRectangleLines(
                rdobj.m_source.x, rdobj.m_source.y, rdobj.m_source.width, rdobj.m_source.height, rdobj.color);
            break;
        case TEXTUREPRO:
            DrawTexturePro(rdobj.m_texture, rdobj.m_source, rdobj.m_dest,
                Vector2 { rdobj.vec4.x, rdobj.vec4.x }, rdobj.vec4.z, rdobj.color);
            break;
        case TEXTURERECT:
            break;
        case RECTREC:
            break;
        case RECTLINEEX:
            break;
        default:;
        }
    }
    renderObjs_2d_bg.clear();
}

void Renderer::Render_2D_colli()
{
    for (auto& rdobj : renderObjs_2d_colli) {
        switch (rdobj.rdt) {
        case TEXT:
            DrawText(rdobj.text, (int)rdobj.m_source.x, (int)rdobj.m_source.y, (int)rdobj.m_source.width,
                rdobj.color);
            break;
        case TEXTURE:
            DrawTexture(rdobj.m_texture, (int)rdobj.m_source.x, (int)rdobj.m_source.y, rdobj.color);
            break;
        case RECTLINE:
            DrawRectangleLines(
                rdobj.m_source.x, rdobj.m_source.y, rdobj.m_source.width, rdobj.m_source.height, rdobj.color);
            break;
        case TEXTUREPRO:
            DrawTexturePro(rdobj.m_texture, rdobj.m_source, rdobj.m_dest,
                Vector2 { rdobj.vec4.x, rdobj.vec4.x }, rdobj.vec4.z, rdobj.color);
            break;
        case TEXTURERECT:
            break;
        case RECTREC: {
            DrawRectangleRec(rdobj.m_source, rdobj.color);
            break;
        }
        case RECTLINEEX: {
            DrawRectangleLinesEx(rdobj.m_source, rdobj.lineThick, rdobj.color);
            break;
        }
        default:;
        }
    }
    renderObjs_2d_colli.clear();
}
