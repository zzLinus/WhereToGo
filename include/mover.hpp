#pragma once
#include <raylib.h>

#include <Renderer.hpp>
#include <string>

class Mover
{
 public:
  Mover(std::string name, Vector2 spownPoint, Renderer* renderer);
  virtual ~Mover();
  virtual void update();
  virtual void upload_drawable();
  virtual void handle_keyboard();
  virtual void upload_hud_drawobj(void);

 private:
 public:
  std::string m_curState;
  std::string m_name;
  Vector2 m_position;
  Rectangle m_collisionBox;
  Renderer* p_renderer;

 private:
};
