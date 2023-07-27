#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <limits.h>
#include <stdlib.h>

#include "game.h"

Entity g_player;
uint64_t g_clock;

int
main ()
{
  //
  init_sdl ();
  init_bullets ();
  init_meteors ();
  init_animationUnits ();

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

  // uint64_t idx = 1;

  // double fps;

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

      play_explosionAnimation ();

      render_scene ();

      for (size_t i = 0; i < ANIMATION_UNIT_COUNT; i++)
        {
          if (g_animationUnits[i]->is_working == true)
            {
              printf ("x_:%i\n", g_animationUnits[i]->rect.x);
              printf ("y_:%i\n", g_animationUnits[i]->rect.x);
              printf ("w_:%i\n", g_animationUnits[i]->rect.w);
              printf ("h_:%i\n", g_animationUnits[i]->rect.h);
            }
        }

      // fps = (double)idx / (g_clock / 1000);
      // if (fps != INFINITY)
      // {
      //     printf("%f\n", fps);
      // }
      // idx++;

      frame_time = SDL_GetTicks64 () - g_clock; // FBS CTRL
      DELAY (frame_time)                        // FBS CTRL
    }
  return EXIT_SUCCESS;
}