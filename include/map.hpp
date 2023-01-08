
#pragma once

#define RAYLIB_TILESON_IMPLEMENTATION
#include "Renderer.hpp"
#include "raylib-tileson.h"
#include "types.hpp"
#include "utils.hpp"
#include <stdio.h>
#include <tileson.hpp>
#include <unordered_map>
#include <vector>

class TileMap {
public:
    TileMap();
    virtual ~TileMap();
    void upload_drawable(void);
    // TODO: make function to get && store all collision object
    void get_collisionRects(void);
    bool check_collision(Rectangle& rect);
    void check_layer(tson::Layer& layer, tson::RaylibTilesonData* data, int posX, int posY, Color tint);

    void upload_tileLayer(tson::Layer& layer, tson::RaylibTilesonData* data, int posX, int posY, Color tint);
    void uplaod_objLayer(tson::Layer& layer, tson::RaylibTilesonData* data, int posX, int posY, Color tint);
    void upload_imgLayer(tson::Layer& layer, tson::RaylibTilesonData* data, int posX, int posY, Color tint);
    Color t_to_r_color(tson::Colori color); // NOTE :conver tiled color to raylib color
    Rectangle t_to_r_rect(tson::Rect rect); // NOTE :conver tiled rectangle to raylib rectangle
private:
public:
    Map* map;
    Vector2 spownPoint;
    std::map<std::string, std::vector<Rectangle>> m_collisionBoxs;

    static Renderer* p_renderer;

private:
    /* data */
};
