#include "Game.hpp"
int main(void)
{
  SetTraceLogLevel(LOG_ALL);
  Game* game = new Game();
  game->Init();
  game->Run();
  delete game;
}
