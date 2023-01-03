#include "mover.hpp"

Mover::Mover(std::string name, Vector2 spownPoint, Renderer* renderer)
    : m_name(name)
    , m_position(spownPoint)
    , m_collisionBox(Rectangle { .x = m_position.x, .y = m_position.y, .width = 50, .height = 100 })
    , p_renderer(renderer)
{
}
Mover::~Mover() { }

void Mover::update() { }

void Mover::upload_drawable() { }

void Mover::handle_keyboard() { }

void Mover::upload_hud_drawobj(void) { }
