#include "cam.hpp"
#include "map.hpp"
#include "player.hpp"
#include <raylib.h>
#include <raymath.h>

class Game {
public:
    Game();
    virtual ~Game();
    void Render();
    void InitEntity();
    void Init();

private:
public:
    // global const here

private:
    Player* player;
    TileMap* tm;
    Cam* cam;
    float deltaTime;
};
