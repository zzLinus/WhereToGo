#pragma once
#include <raylib.h>
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

struct Sprite {
    Texture texture;
    Rectangle frameRec;
    int frameNum;
};
