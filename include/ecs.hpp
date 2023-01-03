#include "cam.hpp"
#include "map.hpp"
#include "mover.hpp"
#include "player.hpp"
#include "types.hpp"
#include <Renderer.hpp>
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

    // TODO: move collison physics here
private:
    void render_map(void);
    void render_movers(void);
    void render_hud(void);

    void update_movers(void);
    void update_cam(void);
    void update_deltaTime(float dt);

public:
    TileMap* p_tm;
    Player* p_player;
    Cam* p_cam;
    Renderer* p_renderer;

private:
    float deltaTime;
};
