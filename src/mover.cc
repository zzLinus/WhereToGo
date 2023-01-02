#include "mover.hpp"

Mover::Mover(std::string name, Vector2 spownPoint)
    : m_name(name)
    , m_position(spownPoint)
    , m_collisionBox(Rectangle { .x = m_position.x, .y = m_position.y, .width = 50, .height = 100 })
{
}
Mover::~Mover() { }

void Mover::update() { }

void Mover::Render() { }

void Mover::handle_keyboard() { }

void Mover::render_hud(void) { }
