#pragma once
#include <raylib.h>
#include <string>

class Mover {
public:
    Mover(std::string name);
    virtual ~Mover();
    virtual void update();
    virtual void Render();
    virtual void handle_keyboard();
    virtual void render_hud(void);

private:
public:
    enum char_state {
        S_IDEL = 0,
        S_RUN,
        S_STOPRUN,
        S_RUN_UP,
        S_RUN_DOWN,
        S_ATTACK1,
        S_ATTACK1_UP,
    };
    std::string m_name;
    Vector2 m_position;

private:
};
