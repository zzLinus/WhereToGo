#pragma once
#include <raylib.h>

#include <vector>

#include "types.hpp"
#include "utils.hpp"

class Renderer
{
 public:
  Renderer();
  virtual ~Renderer();
  void add_renderObj(RenderObject* renderObj, renderMode rm);
  void Render_2D(void);
  void Render_2D_bg(void);
  void Render_2D_colli(void);
  void Render_NORM(void);

 private:
  void Render_2D_mover(float y_dest);

 public:
 private:
  std::vector<RenderObject> renderObjs_2d;
  std::vector<RenderObject> renderObjs_2d_mover;
  std::vector<RenderObject> renderObjs_2d_colli;
  std::vector<RenderObject> renderObjs_norm;
  std::vector<RenderObject> renderObjs_2d_bg;
};
