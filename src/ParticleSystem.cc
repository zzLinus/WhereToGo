#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem()
{
  for (int n = 0; n < MAX_STARS; n++)
    stars[n].Reset();

  for (int n = 0; n < MAX_STARS; n++)
    stars[n].Update(Vector2{ 400, 300 });
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::upload_drawables(Camera2D& cam)
{
  {
    for (int n = 0; n < MAX_STARS; n++)
      stars[n].Update(cam.target);

    for (int n = 0; n < MAX_STARS; n++)
    {
      RenderObject* rdobj;
      // NOTE :Single pixel is just too small these days!
      rdobj = new RenderObject((int)stars[n].pos.x, (int)stars[n].pos.y, 1, 1, Color{ 255, 243, 0, 255 }, RECT);
      p_renderer->add_renderObj(rdobj, RENDER_2D_PATIC);
      delete rdobj;
    }
  }
}
