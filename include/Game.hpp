#include "map.hpp"
#include "player.hpp"
#include <raylib.h>

class Game {
public:
    Game()
        : SCREEN_WIDTH(800)
        , SCREEN_HEIGHT(600) {};
    virtual ~Game();
    void Render();
    void InitEntity();
    void Init();

private:
public:
    // global const here
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;

private:
    Player* player;
    Map* map;
};
