#include "ecs.hpp"
extern bool debugInfo;

Renderer* AnimSprite::p_renderer = Ecs::get_renderer();

Ecs::Ecs()
    : p_tm(nullptr)
    , p_cam(nullptr)
    , deltaTime(0)
{
    p_tm = new TileMap();
    p_cam = new Cam();
    p_player = new Player(Vector2 { 300.0f, 280.0f }, Ecs::get_renderer());
    add_movers(p_player);
    p_tm->get_collisionRects();
}
Ecs::~Ecs()
{
    for (auto& m : movers) {
        delete m;
    }
    delete p_tm;
    delete p_cam;
}

inline void Ecs::add_movers(Mover* m) { movers.push_back(m); }

void Ecs::mover_drawable_upload(void)
{
    for (auto e : movers) {
        e->upload_drawable();
    }
}

void Ecs::update_deltaTime(float dt) { deltaTime = dt; }

void Ecs::update_movers(void)
{
    for (auto m : movers) {
        m->update();
    }
}

void Ecs::render_map() { p_tm->Render(); }

void Ecs::update_cam() { p_cam->UpdateCamera(*p_player, deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT); }

void Ecs::render_component(void)
{
    BeginMode2D(p_cam->cam);
    render_map();
    mover_drawable_upload();

    get_renderer()->Render_2D();
    p_tm->check_collision(p_player->m_collisionBox);
    EndMode2D();
    get_renderer()->Render_NORM();
}

void Ecs::update_component()
{
    update_deltaTime(GetFrameTime());
    update_movers();
    update_cam();
}
