#include "cam.hpp"

Cam::Cam()
{
    cam = { 0 };
    cam.rotation = 0.0f;
    cam.zoom = 4.0f;
}
Cam::~Cam() { }

void Cam::UpdateCamera(Mover& player, float delta, int width, int height)
{
    static int minSpeed = 40;
    static int minEffectLength = 10;
    static int fractionSpeed = 1.0f;

    cam.offset = (Vector2) { (float)width / 2, (float)height / 2 };
    Vector2 diff = Vector2Subtract(player.m_position, cam.target);
    float length = Vector2Length(diff);

    if (length > minEffectLength) {
        int speed = fmaxf(fractionSpeed * length, minSpeed);
        cam.target = Vector2Add(cam.target, Vector2Scale(diff, speed * delta / length));
    }

    static Vector2 bbox = { 0.2f, 0.2f };

    Vector2 bboxWorldMin
        = GetScreenToWorld2D((Vector2) { (1 - bbox.x) * 0.5f * width, (1 - bbox.y) * 0.5f * height }, cam);
    Vector2 bboxWorldMax
        = GetScreenToWorld2D((Vector2) { (1 + bbox.x) * 0.5f * width, (1 + bbox.y) * 0.5f * height }, cam);
    cam.offset = (Vector2) { (1 - bbox.x) * 0.5f * width, (1 - bbox.y) * 0.5f * height };

    if (player.m_position.x < bboxWorldMin.x)
        cam.target.x = player.m_position.x;
    if (player.m_position.y < bboxWorldMin.y)
        cam.target.y = player.m_position.y;
    if (player.m_position.x > bboxWorldMax.x)
        cam.target.x = bboxWorldMin.x + (player.m_position.x - bboxWorldMax.x);
    if (player.m_position.y > bboxWorldMax.y)
        cam.target.y = bboxWorldMin.y + (player.m_position.y - bboxWorldMax.y);
    cam.target.x = (float)((int)(cam.target.x * 100 + .5f)) / 100;
    cam.target.y = (float)((int)(cam.target.y * 100 + .5f)) / 100;
}
