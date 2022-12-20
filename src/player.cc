#include "player.hpp"
#include <raymath.h>
#include <stdio.h>

Player::Player()
{
    frame_rec = nullptr;
    m_frameSpeed = 9;
    m_currentFrame = 0;
    m_frameCounter = 0;
    speed = 3.0f;
    char_current_sprites = char_sprites[0];
    char_current_blade_sprites = char_weapon_blade[0];
    m_current_weapon_state = B_ATTACK1;
    char_tex_frames = 0;
    weapon_tex_frames = 0;
    m_currentState = S_IDEL;
    m_is_left = false;

    position = { 350.0f, 280.0f };

    // load sprites
    char_sprites[S_IDEL].texture = LoadTexture("./assets/whereToGo_charactor_idel.png");
    char_sprites[S_IDEL].frameRec = { 0.0f, 0.0f, (float)char_sprites[S_IDEL].texture.width / 4,
        (float)char_sprites[S_IDEL].texture.height };
    char_sprites[S_IDEL].frameNum = 4;

    char_sprites[S_RUN].texture = LoadTexture("./assets/whereToGo_charactor_run.png");
    char_sprites[S_RUN].frameRec = { 0.0f, 0.0f, (float)char_sprites[S_RUN].texture.width / 7,
        (float)char_sprites[S_RUN].texture.height };
    char_sprites[S_RUN].frameNum = 7;

    char_sprites[S_STOPRUN].texture = LoadTexture("./assets/whereToGo_charactor_stoprun.png");
    char_sprites[S_STOPRUN].frameRec = { 0.0f, 0.0f, (float)char_sprites[S_STOPRUN].texture.width / 5,
        (float)char_sprites[S_STOPRUN].texture.height };
    char_sprites[S_STOPRUN].frameNum = 5;

    char_sprites[S_RUN_UP].texture = LoadTexture("./assets/whereToGo_charactor_runup.png");
    char_sprites[S_RUN_UP].frameRec = { 0.0f, 0.0f, (float)char_sprites[S_RUN_UP].texture.width / 9,
        (float)char_sprites[S_RUN_UP].texture.height };
    char_sprites[S_RUN_UP].frameNum = 9;

    char_sprites[S_RUN_DOWN].texture = LoadTexture("./assets/whereToGo_charactor_rundown.png");
    char_sprites[S_RUN_DOWN].frameRec = { 0.0f, 0.0f, (float)char_sprites[S_RUN_DOWN].texture.width / 9,
        (float)char_sprites[S_RUN_DOWN].texture.height };
    char_sprites[S_RUN_DOWN].frameNum = 9;

    char_sprites[S_ATTACK1].texture = LoadTexture("./assets/whereToGo_charactor_attack1.png");
    char_sprites[S_ATTACK1].frameRec = { 0.0f, 0.0f, (float)char_sprites[S_ATTACK1].texture.width / 6,
        (float)char_sprites[S_ATTACK1].texture.height };
    char_sprites[S_ATTACK1].frameNum = 6;

    char_weapon_blade[B_ATTACK1].texture = LoadTexture("./assets/whereToGo_charactor_weaponblade1.png");
    char_weapon_blade[B_ATTACK1].frameRec
        = { 0.0f, 0.0f, (float)char_weapon_blade[B_ATTACK1].texture.width / 5,
              (float)char_weapon_blade[B_ATTACK1].texture.height };
    char_weapon_blade[B_ATTACK1].frameNum = 5;

    char_sprites[S_ATTACK1_UP].texture = LoadTexture("./assets/whereToGo_charactor_attackup1.png");
    char_sprites[S_ATTACK1_UP].frameRec = { 0.0f, 0.0f, (float)char_sprites[S_ATTACK1_UP].texture.width / 6,
        (float)char_sprites[S_ATTACK1_UP].texture.height };
    char_sprites[S_ATTACK1_UP].frameNum = 6;

    char_weapon_blade[B_ATTACK1_UP].texture = LoadTexture("./assets/whereToGo_charactor_weaponblade2.png");
    char_weapon_blade[B_ATTACK1_UP].frameRec
        = { 0.0f, 0.0f, (float)char_weapon_blade[B_ATTACK1_UP].texture.width / 5,
              (float)char_weapon_blade[B_ATTACK1_UP].texture.height };
    char_weapon_blade[B_ATTACK1_UP].frameNum = 5;

    blade_offset[S_ATTACK1] = Vector2 { .x = 25.0f, .y = 0.0f };
    blade_offset[S_ATTACK1_UP] = Vector2 { .x = 0.0f, .y = -50.0f };
}

bool Player::is_player_attacking()
{
    if ((m_lastState == S_ATTACK1 || m_lastState == S_ATTACK1_UP) && m_currentFrame != 5)
        return true;
    else
        return false;
}

void Player::attack(void)
{
    if (IsKeyDown(KEY_W)) {
        m_currentState = S_ATTACK1_UP;
        m_current_weapon_state = B_ATTACK1_UP;
        m_currentFrame = 0;
        m_frameCounter = 0;
    } else {
        m_currentState = S_ATTACK1;
        m_current_weapon_state = B_ATTACK1;
        m_currentFrame = 0;
        m_frameCounter = 0;
    }

    printf("current frame : %d\n", m_currentFrame);
};

void Player::handle_keyboard()
{
    m_lastState = m_currentState;

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
    position = Vector2Add(position,
        Vector2Multiply(
            Vector2Normalize(Vector2 { direction.x, direction.y }), Vector2 { .x = speed, .y = speed }));

    if (!is_player_attacking()) {
        if (direction.x > 0) {
            m_currentState = S_RUN;
            m_is_left = false;
        } else if (direction.x < 0) {
            m_currentState = S_RUN;
            m_is_left = true;
        } else if (direction.y >= 0) {
            m_currentState = S_RUN_DOWN;
        } else {
            m_currentState = S_RUN_UP;
        }
    }

    if (m_lastState == S_STOPRUN && m_currentFrame != 3) {
        m_currentState = S_STOPRUN;
    }
    if (is_player_attacking()) {
        if (m_currentState == S_ATTACK1_UP) {
            printf("set ATTACK UP!!\n");
            m_currentState = S_ATTACK1_UP;
        } else {
            printf("set ATTACK!!\n");
            m_currentState = S_ATTACK1;
        }
    } else if (direction.x == 0 && direction.y == 0) {
        m_currentState = S_IDEL;
    }

    if (m_lastState == S_RUN && m_currentState == S_IDEL) {
        m_currentState = S_STOPRUN;
        m_currentFrame = 0;
    }

    if (IsKeyDown(KEY_N) && !is_player_attacking()) {
        attack();
    }

    char_tex_frames = char_sprites[m_currentState].frameNum;
    weapon_tex_frames = char_weapon_blade[m_current_weapon_state].frameNum;
    char_current_sprites = char_sprites[m_currentState];
    char_current_blade_sprites = char_weapon_blade[m_current_weapon_state];

    frame_rec = &char_sprites[m_currentState].frameRec;
    if (m_lastState != m_currentState)
        char_sprites[m_lastState].frameRec.x = 0;
};

void Player::Render()
{
    handle_keyboard();
    printf("current strte : %d\n", m_currentState);
    m_frameCounter++;
    if (m_frameCounter >= (60 / m_frameSpeed)) {
        m_frameCounter = 0;
        m_currentFrame++;
        if (m_currentFrame > char_sprites[m_currentState].frameNum - 1)
            m_currentFrame = 0;

        frame_rec->x = (float)m_currentFrame * (float)char_current_sprites.texture.width / char_tex_frames;
        char_weapon_blade[m_current_weapon_state].frameRec.x
            = (float)m_currentFrame * (float)char_current_blade_sprites.texture.width / weapon_tex_frames;
    }

    BeginDrawing();
    ClearBackground(Color { 23, 32, 56 });
    DrawTexture(char_sprites[m_currentState].texture, 15, 40, WHITE);
    DrawRectangleLines(15, 40, char_sprites[m_currentState].texture.width,
        char_sprites[m_currentState].texture.height, LIME);
    DrawRectangleLines(
        15 + (int)frame_rec->x, 40 + (int)frame_rec->y, (int)frame_rec->width, (int)frame_rec->height, RED);

    if (m_is_left) {
        DrawTexturePro(char_sprites[m_currentState].texture,
            Rectangle { .x = frame_rec->x,
                .y = frame_rec->y,
                .width = -frame_rec->width,
                .height = frame_rec->height },
            (Rectangle) { position.x, position.y, (float)frame_rec->width * 3, (float)frame_rec->height * 3 },
            (Vector2) { 0, 1 }, 0.0f, WHITE);
        if (is_player_attacking())
            DrawTexturePro(char_current_blade_sprites.texture,
                Rectangle { .x = char_current_blade_sprites.frameRec.x,
                    .y = char_current_blade_sprites.frameRec.y,
                    .width = -char_current_blade_sprites.frameRec.width,
                    .height = char_current_blade_sprites.frameRec.height },
                Rectangle { position.x - blade_offset[m_currentState].x,
                    position.y + blade_offset[m_currentState].y,
                    (float)char_current_blade_sprites.frameRec.width * 3,
                    (float)char_current_blade_sprites.frameRec.height * 3 },
                Vector2 { 0, 1 }, 0.0f, WHITE);
    } else {
        DrawTexturePro(char_sprites[m_currentState].texture, *frame_rec,
            (Rectangle) { position.x, position.y, (float)frame_rec->width * 3, (float)frame_rec->height * 3 },
            (Vector2) { 0, 1 }, 0.0f, WHITE);
        if (is_player_attacking()) {
            DrawTexturePro(char_current_blade_sprites.texture,
                Rectangle { .x = char_current_blade_sprites.frameRec.x,
                    .y = char_current_blade_sprites.frameRec.y,
                    .width = char_current_blade_sprites.frameRec.width,
                    .height = char_current_blade_sprites.frameRec.height },
                Rectangle { position.x + blade_offset[m_currentState].x,
                    position.y + blade_offset[m_currentState].y,
                    (float)char_current_blade_sprites.frameRec.width * 3,
                    (float)char_current_blade_sprites.frameRec.height * 3 },
                Vector2 { 0, 1 }, 0.0f, WHITE);
        }
    }
    EndDrawing();
}
