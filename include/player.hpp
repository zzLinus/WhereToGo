#include "entity.hpp"
#include "types.hpp"
#include <raylib.h>

class Player : public Entity {
public:
    Player();
    virtual ~Player() {};
    void Render(void) override;
    void handle_keyboard(void) override;
    void attack(void);
    bool load_assets(void);
    bool is_player_attacking(void);

private:
public:
    enum m_weapon_blade {
        B_ATTACK1 = 0,
        B_ATTACK1_UP,
    };
    Sprites char_sprites[10];
    Sprites char_weapon_blade[10];
    Sprites char_current_sprites;
    Sprites char_current_blade_sprites;
    float speed;
    Vector2 position;
    Vector2 blade_offset[10];
    int char_tex_frames;
    int weapon_tex_frames;
    char_state m_currentState;
    m_weapon_blade m_current_weapon_state;
    Rectangle* frame_rec;

private:
};
