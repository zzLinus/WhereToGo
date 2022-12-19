#include "entity.hpp"
#include "types.hpp"
#include <raylib.h>

class Player : public Entity {
public:
    Player();
    virtual ~Player() {};
    void Render() override;
    void handle_keyboard() override;

private:
public:
    Sprites char_sprites[10];
    Vector2 position;
    int tex_frames;
    char_state m_currentState;
    Rectangle* frameRec;

private:
};
