#include "player.hpp"
#include <stdio.h>

Player::Player() {
  frameSpeed = 8;
  currentFrame = 0;
  frameCounter = 0;
  char_idel = LoadTexture("../assets/whereToGo_charactor_idel.png");
  frameRec = {0.0f, 0.0f, (float)char_idel.width / 4, (float)char_idel.height};
  position = {350.0f, 280.0f};
}

void Player::Render() {
  frameCounter++;
  if (frameCounter >= (60 / frameSpeed)) {
    frameCounter = 0;
    currentFrame++;
    if (currentFrame > 3)
      currentFrame = 0;

    frameRec.x = (float)currentFrame * (float)char_idel.width / 4;
  }

  // printf("frameRec : %d | %d\n", frameRec.width, frameRec.height);
  // printf("char_idel: %d | %d\n", char_idel.width, char_idel.height);
  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawTexture(char_idel, 15, 40, WHITE);
  DrawRectangleLines(15, 40, char_idel.width, char_idel.height, LIME);
  DrawRectangleLines(15 + (int)frameRec.x, 40 + (int)frameRec.y,
                     (int)frameRec.width, (int)frameRec.height, RED);

  DrawTexturePro(char_idel, frameRec,
                 (Rectangle){position.x, position.y, (float)frameRec.width * 4,
                             (float)frameRec.height * 4},
                 (Vector2){0, 0}, 0.0f, WHITE);

  EndDrawing();
}
