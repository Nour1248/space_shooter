#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

#include "game.h"

//
void
clear (void)
{
  SDL_RenderClear (g_app.renderer);
}

//
void
render_scene (void)
{
  SDL_RenderPresent (g_app.renderer);
}

//
SDL_Texture *
load_texture (char *filename)
{
  SDL_Texture *texture;
  // SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
  // "Loading %s", filename);
  texture = IMG_LoadTexture (g_app.renderer, filename);
  if (texture == NULL)
    printf ("error:_%s\n", SDL_GetError ());

  return texture;
}

//
void
blit (Entity *entity)
{
  SDL_QueryTexture (entity->texture, NULL, NULL, &entity->rect.w,
                    &entity->rect.h);
  SDL_RenderCopy (g_app.renderer, entity->texture, NULL, &entity->rect);
}

//
void
blit_scaled (Entity *entity, int32_t w, int32_t h)
{
  entity->rect.w = w;
  entity->rect.h = h;
  SDL_RenderCopy (g_app.renderer, entity->texture, NULL, &entity->rect);
}

//
void
blit_scaledAnimation (Animation *a, SDL_Rect *r)
{
  a->rect = *r;
  SDL_RenderCopy (g_app.renderer, a->texture, NULL, &a->rect);
}

//
bool
is_outOfBounds (Entity *e)
{
  if (!(e->rect.x < g_WIDTH && e->rect.x > -(e->rect.w))
      || !(e->rect.y < g_HEIGHT && e->rect.y > -(e->rect.h)))
    return true;
  else
    return false;
}

//
bool
are_colliding (SDL_Rect *r1, SDL_Rect *r2)
{                              // thx mdn
  if (r1->x < r2->x + r2->w && // x axis
      r1->x + r1->w > r2->x && //// //
      r1->y < r2->y + r2->h && // y axis
      r1->y + r1->h > r2->y)   //// //
    return true;
  else
    return false;
}

//
void
animate_player (Entity *entity)
{
  if (g_app.up)
    {
      entity->rect.y -= SHIP_VELOCITY;
    }

  if (g_app.down)
    {
      entity->rect.y += SHIP_VELOCITY;
    }

  if (g_app.left)
    {
      entity->rect.x -= SHIP_VELOCITY;
    }

  if (g_app.right)
    {
      entity->rect.x += SHIP_VELOCITY;
    }
}

//
Entity *g_bullets[BULLETS_COUNT];

//
void
init_bullets (void)
{
  for (size_t i = 0; i < BULLETS_COUNT; i++)
    {
      g_bullets[i] = malloc (sizeof (Entity));
      g_bullets[i]->texture = load_texture ("assets/missile.png");
      g_bullets[i]->hp = 1;
      g_bullets[i]->rect.x = -12334; // just keeping it away for now
    }
}

//
void
blit_bullets (Entity **bulls)
{
  for (size_t i = 0; i < BULLETS_COUNT; i++)
    blit (bulls[i]);
}

//
void
shoot (Entity **bulls, Entity *player)
{
  static size_t i = 0;
  if (g_app.fire)
    {
      if (i == BULLETS_COUNT)
        {
          i = 0;
        }
      bulls[i]->rect.x = player->rect.x + 45;
      bulls[i]->rect.y = player->rect.y - 50;
      g_app.fire = false;
      i++;
    }
}

//
void
animate_bullets (Entity **bulls)
{
  for (size_t i = 0; i < BULLETS_COUNT; i++)
    {
      if (!(is_outOfBounds (bulls[i])))
        {
          bulls[i]->rect.y -= BULLET_VELOCITY;
        }
    }
}

//
Entity *g_meteors[METEORS_COUNT];

//
void
init_meteors (void)
{
  char *meteors[31]
      = { "assets/meteorBrown_small2.png", "assets/meteorBrown_small1.png",
          "assets/meteorBrown_med3.png", "assets/meteorBrown_med1.png" };
  int32_t r;
  for (size_t i = 0; i < METEORS_COUNT; i++)
    {
      r = rand () % 4;
      g_meteors[i] = malloc (sizeof (Entity));
      g_meteors[i]->texture = load_texture (meteors[r]);
      g_meteors[i]->hp = 1;
      g_meteors[i]->rect.x = -FUCK_OFF;
      g_meteors[i]->rect.y = -FUCK_OFF;
      g_meteors[i]->rect.w = 0;
      g_meteors[i]->rect.h = 0;
    }
}

//
void
blit_meteors (Entity **meteors)
{
  for (size_t i = 0; i < METEORS_COUNT; i++)
    {
      if (meteors[i]->texture != NULL && meteors[i]->hp != 0)
        {
          blit_scaled (i[meteors], 50, 50);
        }
    }
}

//
Animation *g_animationUnits[ANIMATION_UNIT_COUNT];

//
void
init_animationUnits (void)
{
  for (size_t i = 0; i < ANIMATION_UNIT_COUNT; i++)
    {
      g_animationUnits[i] = malloc (sizeof (Animation));
      g_animationUnits[i]->texture = NULL;
      g_animationUnits[i]->delay = 300;
      g_animationUnits[i]->idx = 0;
      g_animationUnits[i]->start = 0;
      g_animationUnits[i]->is_working = false;
    }
}

//
char *g_explosionSheet[9]
    = { "assets/regularExplosion00.png", "assets/regularExplosion01.png",
        "assets/regularExplosion02.png", "assets/regularExplosion03.png",
        "assets/regularExplosion04.png", "assets/regularExplosion05.png",
        "assets/regularExplosion06.png", "assets/regularExplosion07.png",
        "assets/regularExplosion08.png" };

//
void
animation (Animation *a, char **sheet, size_t sheet_size)
{
  if (g_clock < a->start + (a->delay * (sheet_size)) && a->is_working == true)
    {
      a->texture = load_texture (sheet[a->idx]);
      SDL_RenderCopy (g_app.renderer, a->texture, NULL, &a->rect);
    }

  if (a->start + (a->delay * (a->idx + 1)) < g_clock && a->is_working == true)
    {
      a->idx++;
    }

  if (a->idx == sheet_size)
    {
      a->idx = 0;
      a->is_working = false;
    }
}

//
void
play_explosionAnimation (void)
{
  for (size_t i = 0; i < ANIMATION_UNIT_COUNT; i++)
    {
      if (g_animationUnits[i]->is_working == true)
        {
          animation (g_animationUnits[i], g_explosionSheet, 9);
        }
    }
}

//
void
animate_meteors (void)
{
  int32_t rx = 50;
  static uint8_t idx = 0;
  for (size_t i = 0; i < METEORS_COUNT; i++)
    {
      for (size_t j = 0; j < BULLETS_COUNT; j++)
        {
          if (are_colliding (&g_meteors[i]->rect, &g_bullets[j]->rect)
              && g_meteors[i]->hp != 0)
            {
              // boom ();
              g_bullets[j]->rect.x = FUCK_OFF;
              g_bullets[j]->rect.y = FUCK_OFF;
              g_animationUnits[idx]->rect = g_meteors[i]->rect;
              g_animationUnits[idx]->start = g_clock;
              g_animationUnits[idx]->is_working = true;
              g_meteors[i]->hp = 0;
              idx++;
              if (idx == ANIMATION_UNIT_COUNT)
                idx = 0;
              break;
            }
        }
      g_meteors[i]->rect.x = 50 + rx;
      g_meteors[i]->rect.y = 200;
      rx += 10;
    }
}
