
#pragma once

#define RAYLIB_TILESON_IMPLEMENTATION
#include "raylib-tileson.h"
#include "utils.hpp"
#include <stdio.h>
#include <tileson.hpp>
#include <unordered_map>
#include <vector>

class TileMap {
public:
    TileMap();
    virtual ~TileMap();
    void Render(void);
    // TODO: make function to get && store all collision object
    void get_collisionRects(void);
    bool check_collision(Rectangle& rect);
    Rectangle RectangleFromTiledRectangle(tson::Rect rect);

public:
    Map* map;
    std::map<std::string, std::vector<Rectangle>> collisions;

private:
    /* data */
};
