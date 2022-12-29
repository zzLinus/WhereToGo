#include "esc.hpp"

Ecs::Ecs() { init_entity(); }
Ecs::~Ecs() { }

inline void Ecs::add_movers(Mover* m) { movers.push_back(m); }

void Ecs::init_entity(void)
{
    Player* p = new Player();
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
