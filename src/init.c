#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int32_t g_WIDTH = 1280;
int32_t g_HEIGHT = 720;
App g_app;

void
init_sdl (void)
{
  if (SDL_Init (SDL_INIT_VIDEO) != 0)
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

  SDL_FreeSurface (icon);

  SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  g_app.renderer
      = SDL_CreateRenderer (g_app.window, -1, SDL_RENDERER_ACCELERATED);

  if (!g_app.renderer)
    {
      printf ("ERROR_SDL_RENDERER : %s\n", SDL_GetError ());
      exit (1);
    }
  IMG_Init (IMG_INIT_PNG | IMG_INIT_JPG);
}