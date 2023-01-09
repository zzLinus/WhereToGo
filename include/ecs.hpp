#include <vector>

#include "Renderer.hpp"
#include "ShaderManager.hpp"
#include "cam.hpp"
#include "map.hpp"
#include "mover.hpp"
#include "player.hpp"
#include "types.hpp"

class Ecs
{
 public:
  Ecs();
  virtual ~Ecs();
  void add_movers(Mover* m);
  void render_component(void);
  void update_component(void);
  void init(void);
  static Renderer* get_renderer(void)
  {
    static Renderer renderer;
    return &renderer;
  }

  Player* get_player(void)
  {
    static Player player(Vector2{ 163.0f, 439.0f }, Ecs::get_renderer());
    return &player;
  }

  // TODO: move collison physics here
 private:
  void upload_mapDrawable(void);
  void mover_drawable_upload(void);

  void update_movers(void);
  void update_cam(void);
  void update_deltaTime(float dt);

 public:
  static Player* p_player;

  TileMap* p_tm;
  Cam* p_cam;
  ShaderManager* p_sdrManager;
  std::vector<Mover*> movers;

 private:
  float deltaTime;
};
