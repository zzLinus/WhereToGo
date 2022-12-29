#include "player.hpp"
#include <iostream>
#include <raymath.h>
#include <stdio.h>

Player::Player()
    : Mover("player")
    , m_frameRec(nullptr)
    , m_frameSpeed(8)
    , m_currentFrame(0)
    , m_frameCounter(0)
    , m_speed(2.0f)
    , m_ctf(0)
    , m_wtf(0)
    , m_curWeaponState(B_ATTACK1)
    , m_curState(S_IDEL)
    , m_isLeft(false)
{
    m_curSprite = m_sprites[0];
    m_curWSprite = m_weaponSprites[0];

    if (load_assets()) {
        TraceLog(LOG_INFO, "Assets load successfully!\n");
    } else {
        TraceLog(LOG_WARNING, "Assets load Failed!\n");
    }
#ifdef DEBUG
    m_showDebug = true;
#endif
}

bool Player::is_player_attacking()
{
    if ((m_lastState == S_ATTACK1) && m_currentFrame != 5)
        return true;
    else
        return false;
}

void Player::attack(void)
{
    m_curState = S_ATTACK1;
    m_curWeaponState = B_ATTACK1;
};

void Player::handle_keyboard()
{
    m_lastState = m_curState;
    if (IsKeyPressed(KEY_D)) {
        m_showDebug = !m_showDebug;
    }

    Vector2 direction = { 0 };
    if (IsKeyDown(KEY_S) && !is_player_attacking()) {
        direction.x = 1.0f;
    }
    if (IsKeyDown(KEY_A) && !is_player_attacking()) {
        direction.x = -1.0f;
    }
    if (IsKeyDown(KEY_W) && !is_player_attacking()) {
        direction.y = -1.0f;
    }
    if (IsKeyDown(KEY_R) && !is_player_attacking()) {
        direction.y = 1.0f;
    }
    m_position = Vector2Add(m_position,
        Vector2Multiply(
            Vector2Normalize(Vector2 { direction.x, direction.y }), Vector2 { .x = m_speed, .y = m_speed }));

    if (!is_player_attacking()) {
        if (direction.x > 0) {
            m_curState = S_RUN;
            m_isLeft = false;
        } else if (direction.x < 0) {
            m_curState = S_RUN;
            m_isLeft = true;
        } else if (direction.y >= 0) {
            m_curState = S_RUN_DOWN;
        } else {
            m_curState = S_RUN_UP;
        }
    }

    if (is_player_attacking()) {
        m_curState = S_ATTACK1;
    } else if (direction.x == 0 && direction.y == 0) {
        m_curState = S_IDEL;
    }

    if (m_lastState == S_RUN && m_curState == S_IDEL) {
        m_curState = S_STOPRUN;
        m_currentFrame = 0;
    }

    if (m_lastState == S_STOPRUN && m_currentFrame != 3) {
        m_curState = S_STOPRUN;
    }

    if (IsKeyDown(KEY_N) && !is_player_attacking()) {
        attack();
    }

    m_ctf = m_sprites[m_curState].frameNum;
    m_wtf = m_weaponSprites[m_curWeaponState].frameNum;
    m_curSprite = m_sprites[m_curState];
    m_curWSprite = m_weaponSprites[m_curWeaponState];

    m_frameRec = &m_sprites[m_curState].frameRec;
    if (m_lastState != m_curState) {
        m_currentFrame = 0;
        m_frameCounter = 0;
        m_frameRec->x = 0.0f;
    }
};

void Player::update()
{
    handle_keyboard();
    m_frameCounter++;
    if (m_frameCounter >= (60 / m_frameSpeed)) {
        m_frameCounter = 0;
        m_currentFrame++;
        if (m_currentFrame > m_sprites[m_curState].frameNum - 1 && m_curState != S_ATTACK1) {
            m_currentFrame = 0;
        } else if (m_currentFrame > m_sprites[m_curState].frameNum) {
            m_currentFrame = 0;
        }

        m_frameRec->x = (float)m_currentFrame * (float)m_curSprite.texture.width / m_ctf;
        m_weaponSprites[m_curWeaponState].frameRec.x
            = (float)m_currentFrame * (float)m_curWSprite.texture.width / m_wtf;
    }
}

void Player::render_hud()
{
#ifdef DEBUG // render debug info
    if (m_showDebug) {
        DrawFPS(SCREEN_WIDTH - 100, 10);
        DrawText("Debug INFO", 15, 20, 10, RAYWHITE);
        DrawTexture(m_sprites[m_curState].texture, 15, 40, WHITE);
        DrawRectangleLines(
            15, 40, m_sprites[m_curState].texture.width, m_sprites[m_curState].texture.height, LIME);
        DrawRectangleLines(15 + (int)m_frameRec->x, 40 + (int)m_frameRec->y, (int)m_frameRec->width,
            (int)m_frameRec->height, RED);
    }
#endif
}

void Player::Render()
{
    ClearBackground(Color { 0, 0, 0 });

    if (m_isLeft) {
        DrawTexturePro(m_sprites[m_curState].texture,
            Rectangle { .x = m_frameRec->x,
                .y = m_frameRec->y,
                .width = -m_frameRec->width,
                .height = m_frameRec->height },
            (Rectangle) { m_position.x, m_position.y, (float)m_frameRec->width, (float)m_frameRec->height },
            (Vector2) { 0, 1 }, 0.0f, WHITE);
        if (is_player_attacking())
            DrawTexturePro(m_curWSprite.texture,
                Rectangle { .x = m_curWSprite.frameRec.x,
                    .y = m_curWSprite.frameRec.y,
                    .width = -m_curWSprite.frameRec.width,
                    .height = m_curWSprite.frameRec.height },
                Rectangle { m_position.x - m_bladeOffset[m_curState].x,
                    m_position.y + m_bladeOffset[m_curState].y, (float)m_curWSprite.frameRec.width,
                    (float)m_curWSprite.frameRec.height },
                Vector2 { 0, 1 }, 0.0f, WHITE);
    } else {
        DrawTexturePro(m_sprites[m_curState].texture, *m_frameRec,
            (Rectangle) { m_position.x, m_position.y, (float)m_frameRec->width, (float)m_frameRec->height },
            (Vector2) { 0, 1 }, 0.0f, WHITE);
        if (is_player_attacking()) {
            DrawTexturePro(m_curWSprite.texture,
                Rectangle { .x = m_curWSprite.frameRec.x,
                    .y = m_curWSprite.frameRec.y,
                    .width = m_curWSprite.frameRec.width,
                    .height = m_curWSprite.frameRec.height },
                Rectangle { m_position.x + m_bladeOffset[m_curState].x,
                    m_position.y + m_bladeOffset[m_curState].y, (float)m_curWSprite.frameRec.width,
                    (float)m_curWSprite.frameRec.height },
                Vector2 { 0, 1 }, 0.0f, WHITE);
        }
    }
}

bool Player::load_assets()
{
    // load sprites
    m_sprites[S_IDEL].texture = LoadTexture("./assets/whereToGo_charactor_idel.png");
    m_sprites[S_IDEL].frameRec
        = { 0.0f, 0.0f, (float)m_sprites[S_IDEL].texture.width / 4, (float)m_sprites[S_IDEL].texture.height };
    m_sprites[S_IDEL].frameNum = 4;

    m_sprites[S_RUN].texture = LoadTexture("./assets/whereToGo_charactor_run.png");
    m_sprites[S_RUN].frameRec
        = { 0.0f, 0.0f, (float)m_sprites[S_RUN].texture.width / 7, (float)m_sprites[S_RUN].texture.height };
    m_sprites[S_RUN].frameNum = 7;

    m_sprites[S_STOPRUN].texture = LoadTexture("./assets/whereToGo_charactor_stoprun.png");
    m_sprites[S_STOPRUN].frameRec = { 0.0f, 0.0f, (float)m_sprites[S_STOPRUN].texture.width / 5,
        (float)m_sprites[S_STOPRUN].texture.height };
    m_sprites[S_STOPRUN].frameNum = 5;

    m_sprites[S_RUN_UP].texture = LoadTexture("./assets/whereToGo_charactor_runup.png");
    m_sprites[S_RUN_UP].frameRec = { 0.0f, 0.0f, (float)m_sprites[S_RUN_UP].texture.width / 9,
        (float)m_sprites[S_RUN_UP].texture.height };
    m_sprites[S_RUN_UP].frameNum = 9;

    m_sprites[S_RUN_DOWN].texture = LoadTexture("./assets/whereToGo_charactor_rundown.png");
    m_sprites[S_RUN_DOWN].frameRec = { 0.0f, 0.0f, (float)m_sprites[S_RUN_DOWN].texture.width / 9,
        (float)m_sprites[S_RUN_DOWN].texture.height };
    m_sprites[S_RUN_DOWN].frameNum = 9;

    m_sprites[S_ATTACK1].texture = LoadTexture("./assets/whereToGo_charactor_attack1.png");
    m_sprites[S_ATTACK1].frameRec = { 0.0f, 0.0f, (float)m_sprites[S_ATTACK1].texture.width / 5,
        (float)m_sprites[S_ATTACK1].texture.height };
    m_sprites[S_ATTACK1].frameNum = 5;

    m_weaponSprites[B_ATTACK1].texture = LoadTexture("./assets/whereToGo_charactor_weaponblade1.png");
    m_weaponSprites[B_ATTACK1].frameRec = { 0.0f, 0.0f, (float)m_weaponSprites[B_ATTACK1].texture.width / 5,
        (float)m_weaponSprites[B_ATTACK1].texture.height };
    m_weaponSprites[B_ATTACK1].frameNum = 5;

    m_bladeOffset[S_ATTACK1] = Vector2 { .x = 10.0f, .y = 0.0f };
    return true;
}
