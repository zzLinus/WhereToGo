#include "map.hpp"
using tson::RaylibTilesonData;
using tson::Rect;

extern DebugInfo debugInfo;

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

bool TileMap::get_collisionRects(Rectangle& rect)
{
    // TODO: add collison detect function
    //
    RaylibTilesonData* data = (RaylibTilesonData*)map->data;
    tson::Map* tsonMap = data->map;
    auto& layers = tsonMap->getLayers();
    bool is_colli = false;
    for (auto& layer : layers) {
        if (layer.getType() == tson::LayerType::ObjectGroup) {
            auto* map = layer.getMap();
            for (auto& obj : layer.getObjects()) {
                if (obj.getObjectType() == tson::ObjectType::Rectangle) {
                    tson::Rect objRect
                        = Rect(obj.getPosition().x, obj.getPosition().y, obj.getSize().x, obj.getSize().y);
                    Rectangle worldRect = RectangleFromTiledRectangle(objRect);
#ifdef DEBUG
                    if ((bool)debugInfo == true) {
                        DrawRectangleRec(worldRect, Color { 255, 255, 255, 100 });
                        DrawRectangleLinesEx(rect, 1, Color { 0, 0, 255, 20 });
                    }
#endif
                    if (CheckCollisionRecs(worldRect, rect))
                        is_colli = true;
                    // break;
                }
            }
            // break;
        }
    }
    return is_colli;
}

Rectangle TileMap::RectangleFromTiledRectangle(tson::Rect rect)
{
    Rectangle output;
    output.x = rect.x;
    output.y = rect.y;
    output.width = rect.width;
    output.height = rect.height;
    return output;
}
