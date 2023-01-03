#include "Renderer.hpp"
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
    static Renderer* get_renderer(void)
    {
        static Renderer renderer;
        return &renderer;
    }

    // TODO: move collison physics here
private:
    void upload_mapDrawable(void);
    void mover_drawable_upload(void);

    void update_movers(void);
    void update_cam(void);
    void update_deltaTime(float dt);

public:
    TileMap* p_tm;
    Player* p_player;
    Cam* p_cam;
    std::vector<Mover*> movers;

private:
    float deltaTime;
};
