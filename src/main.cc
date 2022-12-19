#include "Game.hpp"
int main(void)
{
    Game* game = new Game();
    game->Init();
    game->Render();
    delete game;
    return 0;
}
