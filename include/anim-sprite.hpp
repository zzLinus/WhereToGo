#include "types.hpp"
#include <raylib.h>
#include <string>

class AnimSprite {
public:
    AnimSprite(std::string path, int frameNum, int frameSpeed);
    AnimSprite();
    virtual ~AnimSprite();
    void update_framerect();
    void anim_finished_callback();

public:
    Sprite m_sprite;
    Rectangle m_frameRect;
    int m_frameSpeed;
    int m_frameCounter;
    int m_curFrame;
    bool m_isFinished;

private:
    /* data */
};
