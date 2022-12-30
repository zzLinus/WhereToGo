#include "mover.hpp"

Mover::Mover(std::string name)
    : m_name(name)
    , m_position(Vector2 { 350.0f, 280.0f })
    , m_collisonBox(Rectangle { .x = m_position.x, .y = m_position.y, .width = 25, .height = 50 })
{
}
Mover::~Mover() { }

void Mover::update() { }

void Mover::Render() { }

void Mover::handle_keyboard() { }

void Mover::render_hud(void) { }
