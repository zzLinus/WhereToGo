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
        S_RUN_UP,
        S_RUN_DOWN,
        S_ATTACK1,
        S_ATTACK1_UP,
    };

    int m_frameSpeed;
    int m_currentFrame;
    int m_frameCounter;
    bool m_is_left;
    char_state m_lastState;

private:
};
