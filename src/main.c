#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

Entity g_player;
uint64_t g_clock;

int
main ()
{
  //
  init_sdl ();
  init_bullets ();
  init_meteors ();

  atexit (&clean_up);

  // background
  Entity background;
  background.texture = load_texture ("assets/starfield.png");
  background.rect.x = 0;
  background.rect.y = 0;

  // player ship
  g_player.texture = load_texture ("assets/playerShip1_orange.png");
  g_player.rect.x = (g_WIDTH / 2) - (99 / 2); // centering the ship
  g_player.rect.y = (g_HEIGHT / 2) - (75 / 2);

  uint64_t frame_time;

  Animation *a = malloc (sizeof (Animation));
  a->texture = NULL;
  a->start = 0;
  a->delay = 1000;
  a->idx = 0;
  a->rect.x = 200;
  a->rect.y = 200;
  a->rect.w = 200;
  a->rect.h = 200;

  while (69)
    {
      g_clock = SDL_GetTicks64 (); // FBS CTRL

      clear ();

      SDL_GetWindowSize (g_app.window, &g_WIDTH, &g_HEIGHT);

      handle_input ();

      blit_scaled (&background, g_WIDTH, g_HEIGHT);

      blit (&g_player);

      blit_bullets (g_bullets);

      shoot (g_bullets, &g_player);

      blit_meteors (g_meteors);

      animate_player (&g_player);

      animate_bullets (g_bullets);

      animate_meteors ();

      animation (a, g_explosion, 9);

      render_scene ();

      frame_time = SDL_GetTicks () - g_clock; // FBS CTRL
      DELAY (frame_time)                      // FBS CTRL
    }
  return EXIT_SUCCESS;
}