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
    tm->get_collisionRects();
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
    for (auto m : movers) {
        m->update();
    }
}

void Ecs::render_map() { tm->Render(); }

void Ecs::render_hud(void) { player->render_hud(); }

void Ecs::update_cam() { cam->UpdateCamera(*player, deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT); }

void Ecs::render_component(void)
{
    BeginMode2D(cam->cam);
    render_map();
    render_movers();
    tm->check_collision(player->m_collisionBox);
    EndMode2D();

    render_hud();
}

void Ecs::update_component()
{
    update_deltaTime(GetFrameTime());
    update_cam();
    update_movers();
}
