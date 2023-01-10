#pragma once
#include <raylib.h>
#include <raymath.h>

#include <iostream>

#include "Renderer.hpp"
#include "types.hpp"

#define MAX_SPOTS 1  // NOTE: It must be the same as define in shader
#define MAX_STARS 200

typedef struct Star Star;
struct Star
{
  Vector2 pos;
  Vector2 vel;
  Vector2 lifeTime;
  void Reset()
  {
    pos.x = GetRandomValue(0, SCREEN_WIDTH);
    pos.y = GetRandomValue(0, SCREEN_HEIGHT);
    lifeTime = { 50, (float)GetRandomValue(0, 1) };

    do
    {
      vel.x = (float)cosf32(0);
      vel.y = (float)sinf32(0);

    } while (!(fabs(vel.x) + (fabs(vel.y) > 1)));

    pos = Vector2Add(pos, vel);
  }
  void Update(Vector2 __pos)
  {
    if (GetRandomValue(0, 3) != 0)
      return;

    if (GetRandomValue(0, 3) != 0)
    {
      if ((int)lifeTime.y == 0)
      {
        vel.x = (float)sinf32(lifeTime.x / 50 * PI) * 0.8;
        vel.y = (float)cosf32(lifeTime.x / 50 * PI) * 0.9;
      }
      else
      {
        vel.x = (float)sinf32(-lifeTime.x / 50 * PI) * 0.8;
        vel.y = (float)cosf32(-lifeTime.x / 50 * PI) * 0.9;
      }
    }

    pos = Vector2Add(pos, vel);

    if ((pos.x < pos.x - (float)GetScreenWidth() / 2) || (pos.x > pos.x + (float)GetScreenWidth() / 2) ||
        (pos.y < pos.y - (float)GetScreenHeight() / 2) || (pos.y > pos.y + (float)GetScreenHeight() / 2) ||
        !((int)--lifeTime.x))
    {
      Reset();
    }
  }
};

typedef struct Spot Spot;
struct Spot
{
  Vector2 pos;
  Vector2 vel;
  float inner;
  float radius;

  // Shader locations
  unsigned int posLoc;
  unsigned int innerLoc;
  unsigned int radiusLoc;
  void Reset()
  {
    pos = { 0 };
    vel = { 0 };
    inner = 0.0f;
    radius = 0.0f;
    posLoc = 0;
    innerLoc = 0;
    radiusLoc = 0;
  }
};

class ShaderManager
{
 public:
  ShaderManager();
  virtual ~ShaderManager();
  void upload_drawable(Camera2D& cam);

 private:
 public:
  Star stars[MAX_STARS];
  Spot spots[MAX_SPOTS];

  Shader* shader;
  static Renderer* p_renderer;
  static Vector2 p_playerPos;

 private:
  /* data */
};
