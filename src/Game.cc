#include "Game.hpp"

Game::~Game() { delete player; };

void Game::Init()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Where To Go");
    // Load the texture after calling InitWindow. Textures require a valid OpenGL
    // context.
    InitEntity();
}

void Game::Render()
{
    SetTargetFPS(60);
    BeginDrawing();
    while (!WindowShouldClose()) {
        player->Render();
    }
    EndDrawing();
}

void Game::InitEntity() { player = new Player(); }
