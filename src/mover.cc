#include "mover.hpp"

Mover::Mover(std::string name)
    : m_name(name)
    , m_position(Vector2 { 350.0f, 280.0f })
{
}
Mover::~Mover() { }

void Mover::update() { }

void Mover::Render() { }

void Mover::handle_keyboard() { }

void Mover::render_hud(void) { }
