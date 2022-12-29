#include "types.hpp"

class AnimSprites {
public:
    AnimSprites();
    virtual ~AnimSprites();

public:
    int m_frameSpeed;
    int m_frameCounter;
    int m_curFrame;
    int m_textureFrames;

private:
    /* data */
};
