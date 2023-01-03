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
    TEXTUREPRO,
    RECTLINE,
};

enum renderMode {
    RENDER_2D = 0,
    RENDER_NOR,
};

struct RenderObject {
    Texture2D m_texture;
    Rectangle m_source;
    Rectangle m_dest;
    Color color;
    renderType rdt; // NOTE :rdt -> render data type
    int lineThick;
    int layer;
    char text[64];
    Vector4 vec4;
    RenderObject()
    {
        m_texture = { 0 };
        m_source = { 0 };
        m_dest = { 0 };
        color = { 0 };
        rdt = INVALID;
        lineThick = 0;
        layer = 0;
        vec4 = { 0 };
        strcpy(text, "");
    }
    RenderObject(char* str, int posX, int posY, int fontThick, Color c, renderType t)
        : RenderObject()
    {
        strcpy(text, str);
        m_source.x = (float)posX;
        m_source.y = (float)posY;
        m_source.width = (float)fontThick;
        color = c;
        rdt = t;
    }
    RenderObject(Texture2D texture, int posX, int posY, Color c, renderType t)
        : RenderObject()
    {
        strcpy(text, "");
        m_texture = texture;
        m_source.x = (float)posX;
        m_source.y = (float)posY;
        color = c;
        rdt = t;
    }
    RenderObject(int x, int y, int w, int h, Color c, renderType t)
        : RenderObject()
    {
        strcpy(text, "");
        m_source.x = x;
        m_source.y = y;
        m_source.width = (float)w;
        m_source.height = (float)h;
        color = c;
        rdt = t;
    }
    RenderObject(Texture2D texture, Rectangle source, Rectangle dest, Vector4 v4, Color c, renderType t)
        : RenderObject()
    {
        m_texture = texture;
        m_source = source;
        m_dest = dest;
        vec4 = v4;
        rdt = t;
        color = c;
    }
};
