#pragma once
#include <raylib.h>
#include <raymath.h>

#include <iostream>

#include "Renderer.hpp"
#include "types.hpp"

#define MAX_SPOTS 1  // NOTE: It must be the same as define in shader
#define MAX_STARS 50

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

    do
    {
      vel.x = (float)GetRandomValue(-1000, 1000) / 400.0f;
      vel.y = (float)GetRandomValue(-1000, 1000) / 400.0f;

    } while (!(fabs(vel.x) + (fabs(vel.y) > 1)));

    pos = Vector2Add(pos, vel);
    lifeTime = { 50, 0 };
  }
  void Update(Vector2 __pos)
  {
    if (GetRandomValue(0, 3) != 0)
      return;
    if (GetRandomValue(0, 1) == 0)
      pos = Vector2Add(pos, Vector2{ 0, vel.y });
    else
      pos = Vector2Add(pos, Vector2{ 0, -vel.y });

    if (GetRandomValue(0, 1) == 0)
      pos = Vector2Add(pos, Vector2{ vel.x, 0 });
    else
      pos = Vector2Add(pos, Vector2{ -vel.x, 0 });

    if ((pos.x < 0) || (pos.x > GetScreenWidth()) || (pos.y < 0) || (pos.y > GetScreenHeight()) || !((int)--lifeTime.x))
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
