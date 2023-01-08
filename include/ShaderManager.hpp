#pragma once
#include <raylib.h>
#include <raymath.h>

#include <iostream>

#include "Renderer.hpp"
#include "types.hpp"

#define MAX_SPOTS 3  // NOTE: It must be the same as define in shader
#define MAX_STARS 400

typedef struct Star Star;
struct Star
{
  Vector2 pos;
  Vector2 vel;
  void Reset()
  {
    pos = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

    do
    {
      vel.x = (float)GetRandomValue(-1000, 1000) / 100.0f;
      vel.y = (float)GetRandomValue(-1000, 1000) / 100.0f;

    } while (!(fabs(vel.x) + (fabs(vel.y) > 1)));

    pos = Vector2Add(pos, Vector2Multiply(vel, (Vector2){ 8.0f, 8.0f }));
  }
  void Update()
  {
    pos = Vector2Add(pos, vel);

    if ((pos.x < 0) || (pos.x > GetScreenWidth()) || (pos.y < 0) || (pos.y > GetScreenHeight()))
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
  void upload_drawable(void);

 private:
 public:
  Star stars[MAX_STARS];
  Spot spots[MAX_SPOTS];

  Shader shader;
  static Renderer* p_renderer;

 private:
  /* data */
};
