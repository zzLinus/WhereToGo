#include "ParticleSystem.hpp"

Star ParticleSystem::stars[MAX_STARS];
Texture2D* Star::texture;

ParticleSystem::ParticleSystem()
{
  for (int n = 0; n < MAX_STARS; n++)
    stars[n].Reset();

  for (int n = 0; n < MAX_STARS; n++)
    stars[n].Update();

  Star::texture = new Texture2D(LoadTexture("./assets/basic_circle.png"));
}

ParticleSystem::~ParticleSystem()
{
  delete Star::texture;
}

void ParticleSystem::upload_drawables()
{
  {
    for (int n = 0; n < MAX_STARS; n++)
      stars[n].Update();

    for (int n = 0; n < MAX_STARS; n++)
    {
      RenderObject* rdobj;
      // NOTE :Single pixel is just too small these days!
      rdobj = new RenderObject((int)stars[n].pos.x, (int)stars[n].pos.y, 1, 1, Color{ 255, 243, 0, 255 }, RECT);
      p_renderer->add_renderObj(rdobj, RENDER_2D_PATIC);
      delete rdobj;

      // NOTE :Single pixel is just too small these days!
      rdobj = new RenderObject(
          *stars[n].texture,
          (int)stars[n].pos.x - stars[n].texture->width / 2,
          (int)stars[n].pos.y - stars[n].texture->height / 2,
          Color{ 255, 243, 0, 50 },
          TEXTURE);
      p_renderer->add_renderObj(rdobj, RENDER_2D_PATIC);
      delete rdobj;
    }
  }
}
