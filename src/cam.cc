#include "cam.hpp"

Cam::Cam()
{
    cam = { 0 };
    cam.rotation = 0.0f;
    cam.zoom = 3.0f;
}
Cam::~Cam() { }

void Cam::UpdateCamera(Mover& player, float delta, int width, int height)
{
    static float minSpeed = 30;
    static float minEffectLength = 10;
    static float fractionSpeed = 0.8f;

    cam.offset = (Vector2) { width / 2.0f, height / 2.0f };
    Vector2 diff = Vector2Subtract(player.m_position, cam.target);
    float length = Vector2Length(diff);

    if (length > minEffectLength) {
        float speed = fmaxf(fractionSpeed * length, minSpeed);
        cam.target = Vector2Add(cam.target, Vector2Scale(diff, speed * delta / length));
    }
}
