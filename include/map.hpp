
#pragma once

#define RAYLIB_TILESON_IMPLEMENTATION
#include "raylib-tileson.h"
#include "utils.hpp"
#include <stdio.h>
#include <tileson.hpp>

class TileMap {
public:
    TileMap();
    virtual ~TileMap();
    void Render(void);
    bool get_collisionRects(Rectangle& rect);
    bool check_collision();
    Rectangle RectangleFromTiledRectangle(tson::Rect rect);

public:
    Map* map;

private:
    /* data */
};

// TODO: make function to get && store all collision object
