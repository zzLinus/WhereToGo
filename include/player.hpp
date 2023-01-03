#pragma once

#include "Renderer.hpp"
#include "anim-sprite.hpp"
#include "mover.hpp"

#include <raylib.h>
#include <unordered_map>

class Player : public Mover {
public:
    Player();
    Player(Vector2 spownPoint, Renderer* renderer);
    virtual ~Player() {};
    void update() override;
    void upload_drawable(void) override;
    void upload_hud_drawobj(void) override;
    void handle_keyboard(void) override;
    void attack(void);
    bool load_assets(void);
    bool is_player_attacking(void);

private:
public:
    std::unordered_map<std::string, AnimSprite> m_animSprites;
    std::unordered_map<std::string, AnimSprite> m_weaponBladeSprites;
    std::unordered_map<std::string, Vector2> m_bladeOffset; // NOTE: blade && bollete spawn point

    std::string m_curState;
    std::string m_curWeaponState;
    std::string m_lastState;
    float m_speed;
    bool m_isLeft;

private:
};
