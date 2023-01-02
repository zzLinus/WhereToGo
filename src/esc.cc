#include "esc.hpp"

Ecs::Ecs() { init_entity(); }
Ecs::~Ecs()
{
    for (auto& m : movers) {
        delete m;
    }
}

inline void Ecs::add_movers(Mover* m) { movers.push_back(m); }

void Ecs::init_entity(void)
{
    // TODO: get spwon point from .tmx map file
    Player* p = new Player(Vector2 { 300.0f, 280.0f });
    add_movers(p);
}

void Ecs::render_movers(void)
{
    for (auto e : movers) {
        e->Render();
    }
}

void Ecs::update_movers(void)
{
    for (auto e : movers) {
        e->update();
    }
}

Mover* Ecs::get_player(void)
{
    for (auto e : movers) {
        if (e->m_name.compare("player") == 0)
            return e;
    }
    return nullptr;
}
