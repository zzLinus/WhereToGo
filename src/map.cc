#include "map.hpp"
using tson::RaylibTilesonData;
using tson::Rect;

extern DebugInfo debugInfo;

TileMap::TileMap()
{
    map = new Map();
    spownPoint = { 0 };
    *map = LoadTiled("./assets/map/desert.json");
}
TileMap::~TileMap()
{
    UnloadMap(*map);
    delete map;
}

void TileMap::upload_drawable(void)
{
    int posY = 0;
    int posX = 0;

    RaylibTilesonData* data = (RaylibTilesonData*)map->data;
    if (data == NULL) {
        TraceLog(LOG_WARNING, "TILESON: Cannot draw empty map");
        return;
    }
    tson::Map* tsonMap = data->map;
    auto& layers = tsonMap->getLayers();

    // TODO: Draw the background color.

    for (auto& layer : layers) {
        check_layer(layer, data, posX, posY, WHITE);
    }
}

bool TileMap::check_collision(Rectangle& rect)
{
    bool is_colli = false;
    for (auto& [name, colli_vect] : m_collisionBoxs) {
        for (auto& colli : colli_vect) {
            if (CheckCollisionRecs(rect, colli)) {
                is_colli = true;
                break;
            }
        }
        if (is_colli)
            break;
    }

#ifdef DEBUG
    if ((bool)debugInfo) {
        RenderObject* rdobj;
        if (is_colli)
            rdobj = new RenderObject(rect, Color { 230, 41, 55, 100 }, 1.0f, RECTLINEEX);
        else
            rdobj = new RenderObject(rect, Color { 0, 121, 241, 100 }, 1.0f, RECTLINEEX);

        p_renderer->add_renderObj(rdobj, RENDER_2D_COLLI);
        delete rdobj;
    }
#endif

    return false;
}

void TileMap::get_collisionRects()
{
    // TODO: add collison detect function
    //
    m_collisionBoxs.clear();
    RaylibTilesonData* data = (RaylibTilesonData*)map->data;
    tson::Map* tsonMap = data->map;
    auto& layers = tsonMap->getLayers();
    for (auto& layer : layers) {
        if (layer.getType() == tson::LayerType::ObjectGroup) {
            for (auto& obj : layer.getObjects()) {
                if (obj.getObjectType() == tson::ObjectType::Rectangle) {
                    tson::Rect objRect
                        = Rect(obj.getPosition().x, obj.getPosition().y, obj.getSize().x, obj.getSize().y);
                    Rectangle worldRect = t_to_r_rect(objRect);
                    m_collisionBoxs[obj.getName()].push_back(worldRect);
                }
            }
        }
    }
}

// FIXME :move these mess else where

void TileMap::check_layer(tson::Layer& layer, RaylibTilesonData* data, int posX, int posY, Color tint)
{
    switch (layer.getType()) {
    case tson::LayerType::TileLayer:
        upload_tileLayer(layer, data, posX, posY, tint);
        break;

    case tson::LayerType::ObjectGroup:
        uplaod_objLayer(layer, data, posX, posY, tint);
        break;

    case tson::LayerType::ImageLayer:
        upload_imgLayer(layer, data, posX, posY, tint);
        break;

    case tson::LayerType::Group:
        for (auto& l : layer.getLayers()) {
            check_layer(l, data, posX, posY, tint);
        }
        break;

    default:
        TraceLog(LOG_TRACE, "TILESON: Unsupported layer type");
        break;
    }
}

void TileMap::upload_tileLayer(tson::Layer& layer, RaylibTilesonData* data, int posX, int posY, Color tint)
{
    for (const auto& [pos, tileObject] : layer.getTileObjects()) {
        tson::Tile* tile = tileObject.getTile();
        tson::Tileset* tileset = tileObject.getTile()->getTileset();
        std::string image = tileset->getImage().string();
        if (data->textures.count(image) == 0) {
            continue;
        }

        Texture texture = data->textures[image];
        Rectangle drawRect = t_to_r_rect(tileObject.getDrawingRect());
        tson::Vector2f position = tileObject.getPosition();
        Vector2 drawPos = { position.x + posX, position.y + posY };

        RenderObject* rdobj = new RenderObject(texture, drawRect, drawPos, tint, TEXTURERECT);
        p_renderer->add_renderObj(rdobj, RENDER_2D);
        delete rdobj;
    }
}

void TileMap::uplaod_objLayer(tson::Layer& layer, RaylibTilesonData* data, int posX, int posY, Color tint)
{
    auto* map = layer.getMap();
    for (auto& obj : layer.getObjects()) {
        switch (obj.getObjectType()) {
        case tson::ObjectType::Text: {
            if (obj.isVisible()) {
                auto textObj = obj.getText();
                const char* text = textObj.text.c_str();
                auto color = t_to_r_color(textObj.color);
                auto pos = obj.getPosition();

                // TODO: Find the font size.

                RenderObject* rdobj = new RenderObject(text, posX + pos.x, posY + pos.y, 16, color, TEXT);
                p_renderer->add_renderObj(rdobj, RENDER_2D);
                delete rdobj;
            }
        }
        case tson::ObjectType::Rectangle: {
            tson::Rect objRect
                = Rect(obj.getPosition().x, obj.getPosition().y, obj.getSize().x, obj.getSize().y);
            Rectangle worldRect = t_to_r_rect(objRect);
#ifdef DEBUG
            if ((bool)debugInfo) {
                RenderObject* rdobj = new RenderObject(worldRect, Color { 255, 255, 255, 100 }, RECTREC);
                p_renderer->add_renderObj(rdobj, RENDER_2D_COLLI);
                delete rdobj;
            }
#endif
        }
        default:
            break;
        }
    }
}

void TileMap::upload_imgLayer(tson::Layer& layer, RaylibTilesonData* data, int posX, int posY, Color tint)
{

    NPatchInfo h3PatchInfo
        = { (Rectangle) { 0.0f, 64.0f, 64.0f, 64.0f }, 8, 8, 8, 8, NPATCH_THREE_PATCH_HORIZONTAL };

    auto image = layer.getImage();
    if (data->textures.count(image) == 0) {
        return;
    }

    Texture texture = data->textures[image];
    auto offset = layer.getOffset();

    RenderObject* rdobj = new RenderObject(texture, posX + offset.x, posY + offset.y, tint, TEXTURE);
    if (layer.getName().compare("base_rock") == 0 || layer.getName().compare("bricks") == 0)
        p_renderer->add_renderObj(rdobj, RENDER_2D_BG);
    else
        p_renderer->add_renderObj(rdobj, RENDER_2D);
    delete rdobj;
}

Color TileMap::t_to_r_color(tson::Colori color)
{
    Color output;
    output.r = color.r;
    output.g = color.g;
    output.b = color.b;
    output.a = color.a;
    return output;
}

Rectangle TileMap::t_to_r_rect(tson::Rect rect)
{
    Rectangle output;
    output.x = rect.x;
    output.y = rect.y;
    output.width = rect.width;
    output.height = rect.height;
    return output;
}
