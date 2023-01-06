#pragma once
#include <raylib.h>
#include <string.h>
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

struct Sprite {
    Texture texture;
    int frameNum;
};

enum renderType {
    INVALID = 0,
    TEXT,
    TEXTURE,
    TEXTURERECT,
    TEXTUREPRO,
    RECTLINE,
    RECTLINEEX,
    RECTREC,
};

enum renderMode {
    RENDER_2D = 0,
    RENDER_2D_MOVER,
    RENDER_2D_COLLI,
    RENDER_2D_BG,
    RENDER_NOR,
};

struct RenderObject {
    Texture2D m_texture;
    Rectangle m_source;
    Rectangle m_dest;
    Color color;
    renderType rdt; // NOTE :rdt -> render data type
    float lineThick;
    char text[64];
    Vector4 vec4;
    float y;
    RenderObject()
    {
        m_texture = { 0 };
        m_source = { 0 };
        m_dest = { 0 };
        color = { 0 };
        rdt = INVALID;
        lineThick = 0.0f;
        y = -1;
        vec4 = { 0.0f };
        strcpy(text, "");
    }
    RenderObject(
        const char* str, int posX, int posY, int fontThick, Color c, renderType t) // NOTE :DrawText()
        : RenderObject()
    {
        strcpy(text, str);
        m_source.x = (float)posX;
        m_source.y = (float)posY;
        m_source.width = (float)fontThick;
        color = c;
        rdt = t;
        y = m_source.y;
    }
    RenderObject(Texture2D texture, int posX, int posY, Color c, renderType t) // NOTE :DrawTexture()
        : RenderObject()
    {
        m_texture = texture;
        m_source.x = (float)posX;
        m_source.y = (float)posY;
        color = c;
        rdt = t;
        y = m_source.y + m_texture.height;
    }
    RenderObject(int x, int y, int w, int h, Color c, renderType t) // NOTE :DrawRectangleLines()
        : RenderObject()
    {
        m_source.x = x;
        m_source.y = y;
        m_source.width = (float)w;
        m_source.height = (float)h;
        color = c;
        rdt = t;
        y = m_source.y + m_source.height;
    }
    RenderObject(Texture2D texture, Rectangle source, Rectangle dest, Vector4 v4, Color c, renderType t)
        : RenderObject() // NOTE :DrawTexturePro()
    {
        m_texture = texture;
        m_source = source;
        m_dest = dest;
        vec4 = v4;
        rdt = t;
        color = c;
        y = m_texture.height + m_dest.y;
    }
    RenderObject(Texture2D texture, Rectangle source, Vector2 pos, Color c, renderType t)
        : RenderObject() // NOTE :DrawTextureRec()
    {
        m_texture = texture;
        m_source = source;
        vec4 = Vector4 { .x = pos.x, .y = pos.y };
        rdt = t;
        color = c;
        y = m_texture.height + vec4.y;
    }
    RenderObject(Rectangle rect, Color c, renderType t)
        : RenderObject() // NOTE :DrawRectangleRec()
    {
        m_source = rect;
        color = c;
        rdt = t;
        y = m_source.height + m_source.y;
    }
    RenderObject(Rectangle rect, Color c, float lt, renderType t)
        : RenderObject() // NOTE : DrawRectangleLinesEx()
    {
        m_source = rect;
        lineThick = lt;
        color = c;
        rdt = t;
        y = m_source.height + m_source.y;
    }
};
