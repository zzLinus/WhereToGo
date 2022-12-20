#include "player.hpp"
#include <stdio.h>

Player::Player()
{
    m_frameSpeed = 9;
    m_currentFrame = 0;
    m_frameCounter = 0;
    m_currentState = S_IDEL;
    m_is_left = false;

    position = { 350.0f, 280.0f };

    char_sprites[S_IDEL].texture = LoadTexture("../assets/whereToGo_charactor_idel.png");
    char_sprites[S_IDEL].frameRec = { 0.0f, 0.0f, (float)char_sprites[S_IDEL].texture.width / 4,
        (float)char_sprites[S_IDEL].texture.height };
    char_sprites[S_IDEL].frameNum = 4;

    char_sprites[S_RUN].texture = LoadTexture("../assets/whereToGo_charactor_run.png");
    char_sprites[S_RUN].frameRec = { 0.0f, 0.0f, (float)char_sprites[S_RUN].texture.width / 7,
        (float)char_sprites[S_RUN].texture.height };
    char_sprites[S_RUN].frameNum = 7;

    char_sprites[S_STOPRUN].texture = LoadTexture("../assets/whereToGo_charactor_stoprun.png");
    char_sprites[S_STOPRUN].frameRec = { 0.0f, 0.0f, (float)char_sprites[S_STOPRUN].texture.width / 4,
        (float)char_sprites[S_STOPRUN].texture.height };
    char_sprites[S_STOPRUN].frameNum = 4;

    char_sprites[S_RUN_UP].texture = LoadTexture("../assets/whereToGo_charactor_runup.png");
    char_sprites[S_RUN_UP].frameRec = { 0.0f, 0.0f, (float)char_sprites[S_RUN_UP].texture.width / 9,
        (float)char_sprites[S_RUN_UP].texture.height };
    char_sprites[S_RUN_UP].frameNum = 9;

    char_sprites[S_RUN_DOWN].texture = LoadTexture("../assets/whereToGo_charactor_rundown.png");
    char_sprites[S_RUN_DOWN].frameRec = { 0.0f, 0.0f, (float)char_sprites[S_RUN_DOWN].texture.width / 9,
        (float)char_sprites[S_RUN_DOWN].texture.height };
    char_sprites[S_RUN_DOWN].frameNum = 9;

    char_sprites[S_ATTACK1].texture = LoadTexture("../assets/whereToGo_charactor_attack1.png");
    char_sprites[S_ATTACK1].frameRec = { 0.0f, 0.0f, (float)char_sprites[S_ATTACK1].texture.width / 5,
        (float)char_sprites[S_ATTACK1].texture.height };
    char_sprites[S_ATTACK1].frameNum = 5;

    char_weapon_blade[B_ATTACK1].texture = LoadTexture("../assets/whereToGo_charactor_weaponblade1.png");
    char_weapon_blade[B_ATTACK1].frameRec
        = { 0.0f, 0.0f, (float)char_weapon_blade[B_ATTACK1].texture.width / 5,
              (float)char_weapon_blade[B_ATTACK1].texture.height };
    char_weapon_blade[B_ATTACK1].frameNum = 5;
}

void Player::handle_keyboard()
{
    frameRec = &char_sprites[m_currentState].frameRec;
    m_lastState = m_currentState;
    if (IsKeyDown(KEY_S)) {
        m_is_left = false;
        m_currentState = S_RUN;
    } else if (IsKeyDown(KEY_A)) {
        m_is_left = true;
        m_currentState = S_RUN;
    } else if (IsKeyDown(KEY_W)) {
        m_currentState = S_RUN_UP;
    } else if (IsKeyDown(KEY_R)) {
        m_currentState = S_RUN_DOWN;
    } else if (IsKeyDown(KEY_N)) {
        m_currentState = S_ATTACK1;
        m_currentFrame = 0;
    } else if (m_lastState == S_STOPRUN && m_currentFrame != 3)
        m_currentState = S_STOPRUN;
    else if (m_lastState == S_ATTACK1 && m_currentFrame != 4)
        m_currentState = S_ATTACK1;
    else
        m_currentState = S_IDEL;

    if (m_lastState == S_RUN && m_currentState == S_IDEL) {
        m_currentState = S_STOPRUN;
        m_currentFrame = 0;
    }
};

void Player::Render()
{
    handle_keyboard();
    m_frameCounter++;
    tex_frames = char_sprites[m_currentState].frameNum;
    if (m_frameCounter >= (60 / m_frameSpeed)) {
        m_frameCounter = 0;
        m_currentFrame++;
        if (m_currentFrame > char_sprites[m_currentState].frameNum - 1)
            m_currentFrame = 0;

        frameRec->x = (float)m_currentFrame * (float)char_sprites[m_currentState].texture.width / tex_frames;
        char_weapon_blade[B_ATTACK1].frameRec.x = (float)m_currentFrame
            * (float)char_weapon_blade[B_ATTACK1].texture.width / char_weapon_blade[B_ATTACK1].frameNum;
    }

    BeginDrawing();
    ClearBackground(Color { 23, 32, 56 });
    DrawTexture(char_sprites[m_currentState].texture, 15, 40, WHITE);
    DrawRectangleLines(15, 40, char_sprites[m_currentState].texture.width,
        char_sprites[m_currentState].texture.height, LIME);
    DrawRectangleLines(
        15 + (int)frameRec->x, 40 + (int)frameRec->y, (int)frameRec->width, (int)frameRec->height, RED);

    if (m_is_left) {
        DrawTexturePro(char_sprites[m_currentState].texture,
            Rectangle {
                .x = frameRec->x, .y = frameRec->y, .width = -frameRec->width, .height = frameRec->height },
            (Rectangle) { position.x, position.y, (float)frameRec->width * 3, (float)frameRec->height * 3 },
            (Vector2) { 0, 1 }, 0.0f, WHITE);
        if (m_currentState == S_ATTACK1)
            DrawTexturePro(char_weapon_blade[B_ATTACK1].texture,
                Rectangle { .x = char_weapon_blade[B_ATTACK1].frameRec.x,
                    .y = char_weapon_blade[B_ATTACK1].frameRec.y,
                    .width = -char_weapon_blade[B_ATTACK1].frameRec.width,
                    .height = char_weapon_blade[B_ATTACK1].frameRec.height },
                Rectangle { position.x - 25.0f, position.y,
                    (float)char_weapon_blade[B_ATTACK1].frameRec.width * 3,
                    (float)char_weapon_blade[B_ATTACK1].frameRec.height * 3 },
                Vector2 { 0, 1 }, 0.0f, WHITE);
    } else {
        DrawTexturePro(char_sprites[m_currentState].texture, *frameRec,
            (Rectangle) { position.x, position.y, (float)frameRec->width * 3, (float)frameRec->height * 3 },
            (Vector2) { 0, 1 }, 0.0f, WHITE);
        if (m_currentState == S_ATTACK1)
            DrawTexturePro(char_weapon_blade[B_ATTACK1].texture,
                Rectangle { .x = char_weapon_blade[B_ATTACK1].frameRec.x,
                    .y = char_weapon_blade[B_ATTACK1].frameRec.y,
                    .width = char_weapon_blade[B_ATTACK1].frameRec.width,
                    .height = char_weapon_blade[B_ATTACK1].frameRec.height },
                Rectangle { position.x + 25.0f, position.y,
                    (float)char_weapon_blade[B_ATTACK1].frameRec.width * 3,
                    (float)char_weapon_blade[B_ATTACK1].frameRec.height * 3 },
                Vector2 { 0, 1 }, 0.0f, WHITE);
    }

    EndDrawing();
}
