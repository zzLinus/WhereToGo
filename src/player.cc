#include "player.hpp"
#include "utils.hpp"
#include <iostream>
#include <raymath.h>
#include <stdio.h>

extern DebugInfo debugInfo;

Player::Player()
    : Mover("player", Vector2 { 0.0f, 0.0f }, nullptr)
    , m_speed(1.0f)
    , m_curWeaponState("attack1")
    , m_curState("idel")
    , m_lastState("idel")
    , m_isLeft(false)
{
    if (load_assets()) {
        TraceLog(LOG_INFO, "Assets load successfully!\n");
    } else {
        TraceLog(LOG_WARNING, "Assets load Failed!\n");
    }
}

Player::Player(Vector2 spownPoint, Renderer* renderer)
    : Mover("player", Vector2 { 0.0f, 0.0f }, renderer)
    , m_speed(1.0f)
    , m_curWeaponState("attack1")
    , m_curState("idel")
    , m_lastState("idel")
    , m_isLeft(false)
{
    m_position = spownPoint;
    if (load_assets()) {
        TraceLog(LOG_INFO, "Assets load successfully!\n");
    } else {
        TraceLog(LOG_WARNING, "Assets load Failed!\n");
    }
}

bool Player::is_player_attacking()
{
    if (!m_lastState.compare("attack1") && !m_animSprites[m_curState].m_isFinished) {
        return true;
    } else if (!m_lastState.compare("attack1") && m_animSprites[m_curState].m_isFinished) {
        m_animSprites[m_lastState].anim_finished_callback();
        m_lastState = "";
        return false;
    } else {
        return false;
    }
}

void Player::attack(void)
{
    m_curState = "attack1";
    m_curWeaponState = "attack1";
};

void Player::handle_keyboard()
{
    m_lastState = m_curState;
    if (IsKeyPressed(KEY_D)) {
        debugInfo = debugInfo == DebugInfo::enable ? DebugInfo::disable : DebugInfo::enable;
    }

    Vector2 direction = { 0 };
    if (IsKeyDown(KEY_S) && !is_player_attacking()) {
        direction.x = 1;
    }
    if (IsKeyDown(KEY_A) && !is_player_attacking()) {
        direction.x = -1;
    }
    if (IsKeyDown(KEY_W) && !is_player_attacking()) {
        direction.y = -1;
    }
    if (IsKeyDown(KEY_R) && !is_player_attacking()) {
        direction.y = 1;
    }
    m_position = Vector2Add(m_position,
        Vector2Multiply(
            Vector2Normalize(Vector2 { direction.x, direction.y }), Vector2 { .x = m_speed, .y = m_speed }));

    if (!is_player_attacking()) {
        if (direction.x > 0) {
            m_curState = "run";
            m_isLeft = false;
        } else if (direction.x < 0) {
            m_curState = "run";
            m_isLeft = true;
        } else if (direction.y >= 0) {
            m_curState = "rundown";
        } else {
            m_curState = "runup";
        }
    }

    if (is_player_attacking()) {
        m_curState = "attack1";
    } else if (direction.x == 0 && direction.y == 0) {
        m_curState = "idel";
    }

    if (IsKeyDown(KEY_N) && !is_player_attacking()) {
        attack();
    }
};

void Player::update()
{
    handle_keyboard();
    m_collisionBox.x = m_position.x
        + (float)m_animSprites[m_curState].m_sprite.texture.width
            / (2 * (float)m_animSprites[m_curState].m_sprite.frameNum)
        - 7;
    m_collisionBox.y = m_position.y + (float)m_animSprites[m_curState].m_sprite.texture.height - 6;
    m_collisionBox.width = 14;
    m_collisionBox.height = 6;
    m_animSprites[m_curState].update_framerect();
    if (!m_curState.compare("attack1"))
        m_weaponBladeSprites[m_curWeaponState].update_framerect();
}

void Player::render_hud()
{
#ifdef DEBUG // NOTE :render debug info
    if (debugInfo == DebugInfo::enable) {
        DrawFPS(SCREEN_WIDTH - 100, 10);

        RenderObject* rdobj;

        rdobj = new RenderObject((char*)"Debug INFO", 15, 20, 20, RAYWHITE, TEXT);
        p_renderer->add_renderObj(rdobj);
        delete rdobj;

        rdobj = new RenderObject(m_animSprites[m_curState].m_sprite.texture, 15, 40, WHITE, TEXTURE);
        p_renderer->add_renderObj(rdobj);
        delete rdobj;

        rdobj = new RenderObject(15, 40, m_animSprites[m_curState].m_sprite.texture.width,
            m_animSprites[m_curState].m_sprite.texture.height, LIME, RECTLINE);
        p_renderer->add_renderObj(rdobj);
        delete rdobj;

        rdobj = new RenderObject(15 + (int)m_animSprites[m_curState].m_frameRect.x,
            40 + (int)m_animSprites[m_curState].m_frameRect.y,
            (int)m_animSprites[m_curState].m_frameRect.width,
            (int)m_animSprites[m_curState].m_frameRect.height, RED, RECTLINE);
        p_renderer->add_renderObj(rdobj);
        delete rdobj;

        p_renderer->Render();
    }
#endif
}

void Player::Render()
{
    ClearBackground(Color { 0, 0, 0 });

    m_animSprites[m_curState].render(m_position, m_isLeft);
    Vector2 tmpVect2;
    if (m_isLeft)
        tmpVect2 = Vector2Add(m_position,
            Vector2 { .x = -m_bladeOffset[m_curWeaponState].x, .y = m_bladeOffset[m_curWeaponState].y });
    else
        tmpVect2 = Vector2Add(m_position, m_bladeOffset[m_curWeaponState]);

    m_weaponBladeSprites[m_curWeaponState].render(tmpVect2, m_isLeft);
}

bool Player::load_assets()
{
    // load sprites

    m_animSprites["idel"] = AnimSprite { "./assets/whereToGo_charactor_idel.png", 4, 8 };
    m_animSprites["run"] = AnimSprite { "./assets/wheretogo_charactor_run.png", 6, 11 };
    m_animSprites["runup"] = AnimSprite { "./assets/wheretogo_charactor_runup.png", 6, 11 };
    m_animSprites["rundown"] = AnimSprite { "./assets/wheretogo_charactor_rundown.png", 6, 11 };
    m_animSprites["attack1"] = AnimSprite { "./assets/whereToGo_charactor_attack1.png", 5, 8 };

    // TODO: implement blade offset bullet spown point
    m_weaponBladeSprites["attack1"] = AnimSprite { "./assets/whereToGo_charactor_weaponblade1.png", 5, 8 };

    m_bladeOffset["attack1"] = Vector2 { 12.0f, 2.0f };

    return true;
}
