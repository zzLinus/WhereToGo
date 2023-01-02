#include "cam.hpp"
#include "esc.hpp"
#include "map.hpp"
#include "utils.hpp"
#include <raygui.h>
#include <raylib.h>
#include <raymath.h>

class Game {
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
    TileMap* tm;
    Cam* cam;
    float deltaTime;
    Ecs* ecs;
    Mover* player;
};
