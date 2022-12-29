#include "Game.hpp"

Game::Game()
    : cam(nullptr)
    , tm(nullptr)
    , ecs(nullptr)
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
        deltaTime = GetFrameTime();
        cam->UpdateCamera(*player, deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT);
        BeginDrawing();

        ecs->update_movers();

        // render world && player with camera2D cordinate
        BeginMode2D(cam->cam);
        tm->Render();
        ecs->render_movers();
        EndMode2D();

        player->render_hud();

        EndDrawing();
    }
}

void Game::InitEntity()
{
    cam = new Cam();
    tm = new TileMap();
    ecs = new Ecs();
    player = ecs->get_player();
}

Game::~Game()
{
    delete tm;
    delete cam;
    delete ecs;
};
