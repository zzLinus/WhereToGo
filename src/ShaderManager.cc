#include "ShaderManager.hpp"

ShaderManager::ShaderManager()
{
    for (int n = 0; n < MAX_STARS; n++)
        stars[n].Reset();
    for (int n = 0; n < MAX_SPOTS; n++)
        spots[n].Reset();

    for (int m = 0; m < SCREEN_WIDTH / 2.0; m++) {
        for (int n = 0; n < MAX_STARS; n++)
            stars[n].Update();
    }

    shader = LoadShader(0, "resources/spotlight.fs");

    for (int i = 0; i < MAX_SPOTS; i++) {
        char posName[32] = "spots[x].pos\0";
        char innerName[32] = "spots[x].inner\0";
        char radiusName[32] = "spots[x].radius\0";

        posName[6] = '0' + i;
        innerName[6] = '0' + i;
        radiusName[6] = '0' + i;

        spots[i].posLoc = GetShaderLocation(shader, posName);
        spots[i].innerLoc = GetShaderLocation(shader, innerName);
        spots[i].radiusLoc = GetShaderLocation(shader, radiusName);
    }

    unsigned int wLoc = GetShaderLocation(shader, "screenWidth");
    float sw = (float)GetScreenWidth();
    SetShaderValue(shader, wLoc, &sw, SHADER_UNIFORM_FLOAT);

    for (int i = 0; i < MAX_SPOTS; i++) {
        spots[i].pos.x = (float)GetRandomValue(64, SCREEN_WIDTH - 64);
        spots[i].pos.y = (float)GetRandomValue(64, SCREEN_WIDTH - 64);
        spots[i].vel = (Vector2) { 0, 0 };

        while ((fabs(spots[i].vel.x) + fabs(spots[i].vel.y)) < 2) {
            spots[i].vel.x = GetRandomValue(-400, 40) / 10.0f;
            spots[i].vel.y = GetRandomValue(-400, 40) / 10.0f;
        }

        spots[i].inner = 28.0f * (i + 1);
        spots[i].radius = 60.0f * (i + 1);

        SetShaderValue(shader, spots[i].posLoc, &spots[i].pos.x, SHADER_UNIFORM_VEC2);
        SetShaderValue(shader, spots[i].innerLoc, &spots[i].inner, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, spots[i].radiusLoc, &spots[i].radius, SHADER_UNIFORM_FLOAT);
    }
}

ShaderManager::~ShaderManager() { UnloadShader(shader); }

void ShaderManager::upload_drawable()
{

    for (int n = 0; n < MAX_STARS; n++)
        stars[n].Update();

    RenderObject* rdobj;
    for (int n = 0; n < MAX_STARS; n++) {
        // NOTE :Single pixel is just too small these days!
        rdobj = new RenderObject((int)stars[n].pos.x, (int)stars[n].pos.y, 1, 1, WHITE, RECT);
        p_renderer->add_renderObj(rdobj, RENDER_2D);
        delete rdobj;
    }

    for (int i = 0; i < MAX_SPOTS; i++) {
        if (i == 0) {
            Vector2 mp = GetMousePosition();
            spots[i].pos.x = mp.x;
            spots[i].pos.y = SCREEN_HEIGHT - mp.y;
        } else {
            spots[i].pos.x += spots[i].vel.x;
            spots[i].pos.y += spots[i].vel.y;

            if (spots[i].pos.x < 64)
                spots[i].vel.x = -spots[i].vel.x;
            if (spots[i].pos.x > (SCREEN_WIDTH - 64))
                spots[i].vel.x = -spots[i].vel.x;
            if (spots[i].pos.y < 64)
                spots[i].vel.y = -spots[i].vel.y;
            if (spots[i].pos.y > (SCREEN_HEIGHT - 64))
                spots[i].vel.y = -spots[i].vel.y;
        }

        SetShaderValue(shader, spots[i].posLoc, &spots[i].pos.x, SHADER_UNIFORM_VEC2);
    }
}
