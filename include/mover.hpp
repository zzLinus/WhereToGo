#pragma once
#include <Renderer.hpp>
#include <raylib.h>
#include <string>

class Mover {
public:
    Mover(std::string name, Vector2 spownPoint, Renderer* renderer);
    virtual ~Mover();
    virtual void update();
    virtual void Render();
    virtual void handle_keyboard();
    virtual void render_hud(void);

private:
public:
    std::string m_curState;
    std::string m_name;
    Vector2 m_position;
    Rectangle m_collisionBox;
    Renderer* p_renderer;

private:
};
