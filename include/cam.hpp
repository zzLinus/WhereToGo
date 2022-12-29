#include "player.hpp"
#include <raylib.h>
#include <raymath.h>

class Cam {
public:
    Cam();
    virtual ~Cam();
    void UpdateCamera(Player& player, float delta, int width, int height);

public:
    Camera2D cam;

private:
};
