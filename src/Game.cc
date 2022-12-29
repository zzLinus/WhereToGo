#include "Game.hpp"

Game::Game() { }

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
    while (!WindowShouldClose()) {
        deltaTime = GetFrameTime();
        cam->UpdateCamera(*player, deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT);
        BeginDrawing();

        player->update();
        BeginMode2D(cam->cam);
        tm->Render();
        player->Render();
        EndMode2D();
        player->RenderMenu();

        EndDrawing();
    }
}

void Game::InitEntity()
{
    cam = new Cam();
    tm = new TileMap();
    player = new Player();
}

Game::~Game()
{
    delete player;
    delete tm;
    delete cam;
};
