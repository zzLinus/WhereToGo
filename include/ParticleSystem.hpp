#pragma once
#include <raylib.h>
#include <raymath.h>

#include <iostream>

#include "Renderer.hpp"
#include "types.hpp"
#define MAX_STARS 19

typedef struct Star Star;
struct Star
{
  Vector2 pos;
  Vector2 vel;
  Vector2 lifeTime;
  static Vector2 target;
  static Texture2D* texture;
  void Reset()
  {
    pos.x = GetRandomValue(target.x - (float)SCREEN_WIDTH / (2 * 4), target.x + (float)SCREEN_WIDTH / (2 * 4));
    pos.y = GetRandomValue(target.y - (float)SCREEN_HEIGHT / (2 * 4), target.y + (float)SCREEN_HEIGHT / (2 * 4));
    lifeTime = { 50, (float)GetRandomValue(0, 1) };

    do
    {
      vel.x = (float)cosf32(0);
      vel.y = (float)sinf32(0);

    } while (!(fabs(vel.x) + (fabs(vel.y) > 1)));

    pos = Vector2Add(pos, vel);
  }
  void Update()
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

    if ((pos.x < target.x - (float)SCREEN_WIDTH / (2 * 4)) || (pos.x > target.x + (float)SCREEN_WIDTH / (2 * 4)) ||
        (pos.y < target.y - (float)SCREEN_HEIGHT / (2 * 4)) || (pos.y > target.y + (float)SCREEN_HEIGHT / (2 * 4)) ||
        !((int)--lifeTime.x))
    {
      Reset();
    }
  }
};

class ParticleSystem
{
 public:
  ParticleSystem();
  virtual ~ParticleSystem();
  void upload_drawables();

 private:
 public:
  static Renderer* p_renderer;
  static Star stars[MAX_STARS];

 private:
  /* data */
};
