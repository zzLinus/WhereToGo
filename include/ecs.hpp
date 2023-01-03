#include "cam.hpp"
#include "map.hpp"
#include "mover.hpp"
#include "player.hpp"
#include "types.hpp"
#include <vector>

class Ecs {
public:
    Ecs();
    virtual ~Ecs();
    void add_movers(Mover* m);
    void render_component(void);
    void update_component(void);
    Mover* get_player(void);
    std::vector<Mover*> movers;

private:
    void render_map(void);
    void render_movers(void);
    void render_hud(void);

    void update_movers(void);
    void update_cam(void);
    void update_deltaTime(float dt);

public:
    TileMap* tm;
    Player* player;
    Cam* cam;

private:
    float deltaTime;
};
