
#pragma once

#define RAYLIB_TILESON_IMPLEMENTATION
#include "raylib-tileson.h"
#include <stdio.h>
#include <tileson.hpp>

class TileMap {
public:
    TileMap();
    virtual ~TileMap();
    void Render(void);
    bool check_collision();

public:
    Map* map;

private:
    /* data */
};
