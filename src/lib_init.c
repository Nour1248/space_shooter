#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>

#include "game.h"

int32_t g_WIDTH = 1280;
int32_t g_HEIGHT = 720;

void
init_libs (void)
{
  if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0)
    {
      printf ("ERROR_SDL_INIT: %s\n", SDL_GetError ());
      exit (1);
    }

  g_app.window = SDL_CreateWindow (
      "Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, g_WIDTH,
      g_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALWAYS_ON_TOP);
  if (!g_app.window)
    {
      printf ("ERROR_SDL_WINDOW : %s\n", SDL_GetError ());
      exit (1);
    }

  SDL_Surface *icon = IMG_Load ("assets/shield_gold.png");

  SDL_SetWindowIcon (g_app.window, icon);

  SDL_FreeSurface (icon); // IMPORTANTE`

  SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  g_app.renderer = SDL_CreateRenderer (
      g_app.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!g_app.renderer)
    {
      printf ("ERROR_SDL_RENDERER : %s\n", SDL_GetError ());
      exit (1);
    }
  IMG_Init (IMG_INIT_PNG);
  Mix_Init (MIX_INIT_OGG);
}

void
clean_up (void)
{
  for (size_t i = 0; i < BULLETS_COUNT; i++)
    {
      free (g_bullets[i]);
    }
  for (size_t i = 0; i < METEORS_COUNT; i++)
    {
      free (g_meteors[i]);
    }
  for (size_t i = 0; i < ANIMATION_UNIT_COUNT; i++)
  {
    free (g_animationUnits[i]);
  }

  SDL_DestroyRenderer (g_app.renderer);
  SDL_DestroyWindow (g_app.window);
  SDL_Quit ();

  IMG_Quit ();

  Mix_CloseAudio ();
  Mix_FreeChunk (g_boomChunk);
  Mix_FreeChunk (g_pewpewChunk);
  Mix_FreeMusic (g_uiMusic);
  Mix_Quit ();
}