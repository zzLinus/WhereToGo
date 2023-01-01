#pragma once

#include "mover.hpp"
#include "types.hpp"
#include <raylib.h>

class Player : public Mover {
public:
    Player();
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
    enum m_weapon_blade {
        B_ATTACK1 = 0,
    };
    Sprite m_sprites[10];
    Sprite m_weaponSprites[10];
    Sprite m_curSprite;
    Sprite m_curWSprite;
    float m_speed;
    Vector2 m_bladeOffset[10];
    // TODO: create a animation texture class for these mess
    int m_ctf; // charactor texture frames
    int m_wtf; // weapon texture frames
    char_state m_curState;
    m_weapon_blade m_curWeaponState;
    Rectangle* m_frameRec;
    int m_frameSpeed;
    int m_currentFrame;
    int m_frameCounter;
    bool m_isLeft;
    char_state m_lastState;

private:
};
