#include "ShaderManager.hpp"

Vector2 ShaderManager::p_playerPos;

ShaderManager::ShaderManager()
{
  for (int n = 0; n < MAX_SPOTS; n++)
    spots[n].Reset();

  shader = new Shader(LoadShader(0, "resources/fs_spotlight.glsl"));

  for (int i = 0; i < MAX_SPOTS; i++)
  {
    const char* posName = TextFormat("spots[%d].pos\0", i);
    const char* innerName = TextFormat("spots[%d].inner\0", i);
    const char* radiusName = TextFormat("spots[%d].radius\0", i);

    spots[i].posLoc = GetShaderLocation(*shader, posName);
    spots[i].innerLoc = GetShaderLocation(*shader, innerName);
    spots[i].radiusLoc = GetShaderLocation(*shader, radiusName);
  }

  unsigned int wLoc = GetShaderLocation(*shader, "screenWidth");
  float sw = (float)GetScreenWidth();
  SetShaderValue(*shader, wLoc, &sw, SHADER_UNIFORM_FLOAT);

  for (int i = 0; i < MAX_SPOTS; i++)
  {
    spots[i].pos.x = (float)GetRandomValue(64, SCREEN_WIDTH - 64);
    spots[i].pos.y = (float)GetRandomValue(64, SCREEN_WIDTH - 64);
    spots[i].vel = (Vector2){ 0, 0 };

    while ((fabs(spots[i].vel.x) + fabs(spots[i].vel.y)) < 2)
    {
      spots[i].vel.x = GetRandomValue(-400, 40) / 10.0f;
      spots[i].vel.y = GetRandomValue(-400, 40) / 10.0f;
    }

    spots[i].inner = 28.0f * (i + 1);
    spots[i].radius = 260.0f * (i + 1);

    SetShaderValue(*shader, spots[i].posLoc, &spots[i].pos.x, SHADER_UNIFORM_VEC2);
    SetShaderValue(*shader, spots[i].innerLoc, &spots[i].inner, SHADER_UNIFORM_FLOAT);
    SetShaderValue(*shader, spots[i].radiusLoc, &spots[i].radius, SHADER_UNIFORM_FLOAT);
  }
}

ShaderManager::~ShaderManager()
{
  UnloadShader(*shader);
  delete shader;
}

void ShaderManager::update_Shaders(Camera2D& cam)
{
  for (int i = 0; i < MAX_SPOTS; i++)
  {
    if (i == 0)
    {
      Vector2 mp = GetWorldToScreen2D(p_playerPos, cam);
      // Vector2 mp = GetMousePosition();
      spots[i].pos.x = mp.x;
      spots[i].pos.y = SCREEN_HEIGHT - mp.y;
    }
    else
    {
      spots[i].pos.x += spots[i].vel.x;
      spots[i].pos.y += spots[i].vel.y;

      if (spots[i].pos.x < 64)
        spots[i].vel.x = -spots[i].vel.x;
      if (spots[i].pos.x > (SCREEN_WIDTH - 64))
        spots[i].vel.x = -spots[i].vel.x;
      if (spots[i].pos.y < 64)
        spots[i].vel.y = -spots[i].vel.y;
      if (spots[i].pos.y > (SCREEN_HEIGHT - 64))
        spots[i].vel.y = -spots[i].vel.y;
    }

    SetShaderValue(*shader, spots[i].posLoc, &spots[i].pos.x, SHADER_UNIFORM_VEC2);
  }
}
