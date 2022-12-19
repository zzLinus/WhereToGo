#include <raylib.h>
class Entity {
public:
    Entity() {};
    virtual ~Entity() {};
    virtual void Render() {};
    virtual void handle_keyboard() {};

private:
public:
    enum char_state {
        S_IDEL = 0,
        S_RUN,
        S_STOPRUN,
    };

    int m_frameSpeed;
    int m_currentFrame;
    int m_frameCounter;
    bool m_is_left;
    char_state m_lastState;

private:
};
