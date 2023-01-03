#include "anim-sprite.hpp"
AnimSprite::AnimSprite() { }

AnimSprite::AnimSprite(std::string path, int frameNum, int frameSpeed)
    : m_frameSpeed(frameSpeed)
    , m_frameCounter(0)
    , m_curFrame(0)
    , m_frameRect(Rectangle { 0.0f })
    , m_isFinished(false)
{
    m_sprite.texture = LoadTexture(path.c_str());
    m_sprite.frameNum = frameNum;

    m_frameRect = Rectangle {
        0.0f,
        0.0f,
        (float)m_sprite.texture.width / frameNum,
        (float)m_sprite.texture.height,
    };
}
AnimSprite::~AnimSprite() { }

void AnimSprite::update_framerect()
{
    m_frameCounter++;
    if (m_frameCounter >= (60 / m_frameSpeed)) {
        m_frameCounter = 0;
        m_curFrame++;
        if (m_curFrame > m_sprite.frameNum) {
            m_curFrame = 0;
            m_isFinished = true;
        }

        // NOTE: update frameRect
        m_frameRect.x = (float)m_curFrame * (float)m_sprite.texture.width / m_sprite.frameNum;
    }
}

void AnimSprite::anim_finished_callback() { m_isFinished = false; }

void AnimSprite::render(Vector2 position, bool invert)
{
    float w;
    if (invert)
        w = -m_frameRect.width;
    else
        w = m_frameRect.width;

    DrawTexturePro(m_sprite.texture,
        Rectangle { .x = m_frameRect.x, .y = m_frameRect.y, .width = w, .height = m_frameRect.height },
        (Rectangle) { position.x, position.y, (float)m_frameRect.width, (float)m_frameRect.height },
        (Vector2) { 0, 1 }, 0.0f, WHITE);
}
