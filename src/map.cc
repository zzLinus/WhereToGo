#include "map.hpp"

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
