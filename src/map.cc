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
    bool is_colli = false;
    for (auto& [name, colli_vect] : m_collisionBoxs) {
        for (auto& colli : colli_vect) {
            if ((bool)debugInfo)
                DrawRectangleRec(colli, Color { 255, 255, 255, 100 });
            if (CheckCollisionRecs(rect, colli)) {
                is_colli = true;
            }
        }
    }

#ifdef DEBUG
    if ((bool)debugInfo) {
        if (is_colli)
            DrawRectangleLinesEx(rect, 1, Color { 230, 41, 55, 100 });
        else
            DrawRectangleLinesEx(rect, 1, Color { 0, 121, 241, 100 });
    }
#endif

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
                    m_collisionBoxs[obj.getName()].push_back(worldRect);
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
