#include "ecs.hpp"
extern bool debugInfo;

Ecs::Ecs()
    : tm(nullptr)
    , cam(nullptr)
    , deltaTime(0)
{
    tm = new TileMap();
    cam = new Cam();
    player = new Player(Vector2 { 300.0f, 280.0f });
    add_movers(player);
}
Ecs::~Ecs()
{
    for (auto& m : movers) {
        delete m;
    }
    delete tm;
    delete cam;
}

inline void Ecs::add_movers(Mover* m) { movers.push_back(m); }

void Ecs::render_movers(void)
{
    for (auto e : movers) {
        e->Render();
    }
}

void Ecs::update_deltaTime(float dt) { deltaTime = dt; }

void Ecs::update_movers(void)
{
    for (auto e : movers) {
        e->update();
    }
}

void Ecs::render_map()
{
    tm->Render();
#ifdef DEBUG
    // TODO: Implement collision may be make a map store each type of collison object and
    if ((bool)debugInfo) {
        // TODO: if draw text above player using player.position will glitch because text only draw using
        // int value
        if (CheckCollision(tm->map, &player->m_collisionBox, true))
            DrawText("Collision : True", player->m_position.x, player->m_position.y - 10, 10, RED);
        else
            DrawText("Collision : False", player->m_position.x, player->m_position.y - 10, 10, GREEN);
    }
#else
    CheckCollision(tm->map, &player->m_collisonBox, false);
#endif
}

void Ecs::render_hud(void) { player->render_hud(); }

void Ecs::update_cam() { cam->UpdateCamera(*player, deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT); }

void Ecs::render_component(void)
{
    BeginMode2D(cam->cam);
    render_map();
    render_movers();
    EndMode2D();

    render_hud();
}

void Ecs::update_component()
{
    update_deltaTime(GetFrameTime());
    update_cam();
    update_movers();
}
