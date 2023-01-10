#pragma once
#include <raylib.h>
#include <raymath.h>

#include <iostream>

#include "Renderer.hpp"
#include "types.hpp"

#define MAX_SPOTS 1  // NOTE: It must be the same as define in shader

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
  void update_Shaders(Camera2D& cam);

 private:
 public:
  Spot spots[MAX_SPOTS];

  Shader* shader;
  static Vector2 p_playerPos;

 private:
  /* data */
};
