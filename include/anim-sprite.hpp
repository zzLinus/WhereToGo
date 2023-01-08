#include <raylib.h>

#include <string>

#include "Renderer.hpp"
#include "types.hpp"

class AnimSprite
{
 public:
  AnimSprite(std::string path, int frameNum, int frameSpeed);
  AnimSprite();
  virtual ~AnimSprite();
  void update_framerect();
  void anim_finished_callback();
  void upload_drawable(Vector2 position, bool invert);

 public:
  Sprite m_sprite;
  Rectangle m_frameRect;
  int m_frameSpeed;
  int m_frameCounter;
  int m_curFrame;
  bool m_isFinished;

  static Renderer* p_renderer;

 private:
  /* data */
};
