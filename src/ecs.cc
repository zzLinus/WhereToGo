#include "ecs.hpp"
extern bool debugInfo;

Renderer* AnimSprite::p_renderer = Ecs::get_renderer();
Renderer* TileMap::p_renderer = Ecs::get_renderer();
Renderer* ParticleSystem::p_renderer = Ecs::get_renderer();

Vector2 Star::target;

// NOTE :for linkage usage
Player* Ecs::p_player;
Cam* Ecs::p_cam;

Ecs::Ecs() : p_tm(nullptr), deltaTime(0)
{
  p_tm = new TileMap();
  p_cam = new Cam();
  p_sdrManager = new ShaderManager();
  p_particleSystem = new ParticleSystem();
  Star::target = p_cam->cam.target;
}
Ecs::~Ecs()
{
  for (auto& m : movers)
  {
    delete m;
  }
  delete p_tm;
  delete p_cam;
  delete p_sdrManager;
  delete p_particleSystem;
}

inline void Ecs::add_movers(Mover* m)
{
  movers.push_back(m);
}

void Ecs::mover_drawable_upload(void)
{
  for (auto e : movers)
  {
    e->upload_drawable();
  }
}

void Ecs::update_deltaTime(float dt)
{
  deltaTime = dt;
}

void Ecs::update_movers(void)
{
  for (auto m : movers)
  {
    m->update();
  }
}

void Ecs::init()
{
  upload_mapDrawable();
  p_player = get_player();
  add_movers(p_player);
  ShaderManager::p_playerPos = Ecs::get_player()->m_position;
}

void Ecs::upload_mapDrawable()
{
  p_tm->upload_drawable();
}

void Ecs::update_cam()
{
  p_cam->UpdateCamera(*p_player, deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Ecs::render_component(void)
{
  p_tm->get_collisionRects();
  p_tm->check_collision(p_player->m_collisionBox);

  BeginMode2D(p_cam->cam);

  get_renderer()->Render_2D_bg();
  get_renderer()->Render_2D();
  get_renderer()->Render_2D_colli();
  get_renderer()->Render_2D_particles();

  EndMode2D();

  RenderTexture2D fogOfWar = LoadRenderTexture(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
  SetTextureFilter(fogOfWar.texture, TEXTURE_FILTER_BILINEAR);

  BeginTextureMode(fogOfWar);
  DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 1));
  DrawCircle(400, 300, 50, WHITE);
  EndTextureMode();

  DrawTexture(fogOfWar.texture, 0, 0, Fade(WHITE, 1));

  get_renderer()->Render_NORM();

  BeginShaderMode(*p_sdrManager->shader);
  DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
  EndShaderMode();

  UnloadRenderTexture(fogOfWar);  // Unload render texture

  if (debugInfo)
    DrawFPS(SCREEN_WIDTH - 100, 30);
}

void Ecs::update_component()
{
  update_deltaTime(GetFrameTime());

  ShaderManager::p_playerPos = Ecs::get_player()->get_center();
  p_sdrManager->update_Shaders(p_cam->cam);

  update_movers();
  update_cam();

  Star::target = p_cam->cam.target;
}

void Ecs::upload_drawable()
{
  upload_mapDrawable();
  mover_drawable_upload();
  p_particleSystem->upload_drawables();
}
