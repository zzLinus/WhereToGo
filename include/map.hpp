
#define RAYLIB_TILESON_IMPLEMENTATION
#include "raylib-tileson.h"
#include <stdio.h>

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
