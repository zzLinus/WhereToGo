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
