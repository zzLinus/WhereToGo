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
    RECTLINE,
};

struct RenderObject {
    Texture2D m_texture;
    Rectangle source;
    Rectangle dest;
    Color color;
    renderType rdt; // NOTE :rdt -> render data type
    int lineThick;
    int layer;
    char text[64];
    RenderObject()
    {
        m_texture = { 0 };
        source = { 0 };
        dest = { 0 };
        color = { 0 };
        rdt = INVALID;
        lineThick = 0;
        layer = 0;
        strcpy(text, "");
    }
    RenderObject(char* str, int posX, int posY, int fontThick, Color c, renderType t)
        : RenderObject()
    {
        strcpy(text, str);
        source.x = (float)posX;
        source.y = (float)posY;
        source.width = (float)fontThick;
        color = c;
        rdt = t;
    }
    RenderObject(Texture2D texture, int posX, int posY, Color c, renderType t)
        : RenderObject()
    {
        strcpy(text, "");
        m_texture = texture;
        source.x = (float)posX;
        source.y = (float)posY;
        color = c;
        rdt = t;
    }
    RenderObject(int x, int y, int w, int h, Color c, renderType t)
        : RenderObject()
    {
        strcpy(text, "");
        source.x = x;
        source.y = y;
        source.width = (float)w;
        source.height = (float)h;
        color = c;
        rdt = t;
    }
};
