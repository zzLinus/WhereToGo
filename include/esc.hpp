#include "mover.hpp"
#include "player.hpp"
#include <vector>

class Ecs {
public:
    Ecs();
    virtual ~Ecs();
    void add_movers(Mover* m);
    inline void init_entity(void);
    void render_movers(void);
    void update_movers(void);
    Mover* get_player(void);
    std::vector<Mover*> movers;

private:
public:
};
