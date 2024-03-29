#include <raylib.h>
#include <raymath.h>

#include "ecs.hpp"
#include "utils.hpp"

class Game
{
 public:
  Game();
  virtual ~Game();
  void Run();
  void InitEntity();
  void Init();

 private:
 public:
  // global const here

 private:
  float deltaTime;
  Ecs* ecs;
};
