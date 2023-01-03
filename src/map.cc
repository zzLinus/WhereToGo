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

bool TileMap::check_collision(Rectangle& rect)
{
    // WARN : what the fuck is happening here
    bool is_colli = false;
    for (auto& [name, colli_vect] : collisions) {
        for (auto& colli : colli_vect) {
            DrawRectangleRec(colli, WHITE);
            if (CheckCollisionRecs(rect, colli)) {
                is_colli = true;
            }
        }
    }

    if (is_colli)
        DrawRectangleLinesEx(rect, 1, RED);
    else
        DrawRectangleLinesEx(rect, 1, BLUE);

    return false;
}

void TileMap::get_collisionRects()
{
    // TODO: add collison detect function
    //
    RaylibTilesonData* data = (RaylibTilesonData*)map->data;
    tson::Map* tsonMap = data->map;
    auto& layers = tsonMap->getLayers();
    for (auto& layer : layers) {
        if (layer.getType() == tson::LayerType::ObjectGroup) {
            for (auto& obj : layer.getObjects()) {
                if (obj.getObjectType() == tson::ObjectType::Rectangle) {
                    tson::Rect objRect
                        = Rect(obj.getPosition().x, obj.getPosition().y, obj.getSize().x, obj.getSize().y);
                    Rectangle worldRect = RectangleFromTiledRectangle(objRect);
                    collisions[obj.getName()].push_back(worldRect);
                }
            }
        }
    }
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
