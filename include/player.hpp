#include "entity.hpp"
#include <raylib.h>

class Player : public Entity {
public:
  Player();
  virtual ~Player(){};
  void Render() override;
  Texture2D char_idel;
  Vector2 position;
  Rectangle frameRec;

private:
};
