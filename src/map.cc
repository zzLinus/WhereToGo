#include "map.hpp"
using tson::RaylibTilesonData;

TileMap::TileMap()
{
    map = new Map();
    *map = LoadTiled("./assets/map/desert.json");
}
TileMap::~TileMap()
{
    UnloadMap(*map);
    delete map;
}

void TileMap::Render(void) { DrawTiled(*map, 0, 0, WHITE); }

bool TileMap::check_collision()
{
    for (;;) { }
    return false;
}
