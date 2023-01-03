#include "Game.hpp"
#include <iostream>

#ifdef DEBUG
DebugInfo debugInfo = DebugInfo::enable;
#else
DebugInfo debugInfo = DebugInfo::disable;
#endif

Game::Game()
    : ecs(nullptr)
{
}

void Game::Init()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Where To Go");
    // NOTE: Load the texture after calling InitWindow. Textures require a valid OpenGL context.

    InitEntity();
}

void Game::Run()
{
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        ecs->update_component();
        BeginDrawing();

        // render && player with camera2D cordinate
        ecs->render_component();

        EndDrawing();
    }
}

void Game::InitEntity() { ecs = new Ecs(); }

Game::~Game() { delete ecs; };
