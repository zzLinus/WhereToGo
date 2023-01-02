#pragma once

#include "anim-sprite.hpp"
#include "mover.hpp"
#include "types.hpp"
#include <raylib.h>
#include <unordered_map>

class Player : public Mover {
public:
    Player();
    Player(Vector2 spownPoint);
    virtual ~Player() {};
    void update() override;
    void Render(void) override;
    void render_hud(void) override;
    void handle_keyboard(void) override;
    void attack(void);
    bool load_assets(void);
    bool is_player_attacking(void);

private:
public:
    std::unordered_map<std::string, AnimSprite> m_animSprites;
    std::unordered_map<std::string, AnimSprite> m_weaponBladeSprites;
    std::unordered_map<std::string, Vector2> m_bladeOffset; // NOTE: blade && bollete spawn point
    float m_speed;

    // TODO: create a animation texture class for these mess
    std::string m_curState;
    std::string m_curWeaponState;
    bool m_isLeft;
    std::string m_lastState;

private:
};
