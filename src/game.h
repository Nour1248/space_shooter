#ifndef _GAME_H
#define _GAME_H 69

#ifdef __cplusplus
extern "C"
{
#endif

#include "structs.h"
#include <SDL2/SDL.h>
#include <pthread.h>
#include <stdbool.h>

#define FPS 60
#define DELTA 1000 / FPS // AKA FRAME DELAY
#define FUCK_OFF 6969

#define BULLETS_COUNT 50
#define METEORS_COUNT 50
#define ANIMATION_UNIT_COUNT 20

#define SHIP_VELOCITY 20
#define BULLET_VELOCITY 10

#define DELAY(ft)                                                             \
  if (ft < DELTA)                                                             \
    {                                                                         \
      SDL_Delay (DELTA - ft);                                                 \
    }

  // global objs/vars
  extern int32_t g_WIDTH;

  extern int32_t g_HEIGHT;

  extern uint64_t g_clock;

  extern App g_app;

  extern Entity g_player;

  extern Entity *g_bullets[BULLETS_COUNT];

  extern Entity *g_meteors[METEORS_COUNT];

  extern char *g_explosion[9];

  // init protos
  extern void init_sdl (void);

  // input protos
  extern void handle_input (void);

  extern void handle_keydown (SDL_KeyboardEvent *event);

  extern void handle_keyup (SDL_KeyboardEvent *event);

  // draw protos
  extern void clean_up (void);

  extern void clear (void);

  extern void render_scene (void);

  extern SDL_Texture *load_texture (char *filename);

  extern void blit (Entity *entity);

  extern void blit_scaled (Entity *entity, int32_t w, int32_t h);

  extern void blit_scaledAnimation (Animation *a, SDL_Rect *r);

  extern bool is_outOfBounds (Entity *e);

  extern bool are_colliding (SDL_Rect *r1, SDL_Rect *r2);

  extern void animate_player (Entity *entity);

  extern void init_bullets (void);

  extern void blit_bullets (Entity **bulls);

  extern void shoot (Entity **bulls, Entity *player);

  extern void animate_bullets (Entity **bulls);

  extern void init_meteors (void);

  extern void blit_meteors (Entity **meteors);

  extern void animate_meteors (void);

  extern void animation (Animation *a, char **sheet, size_t sheet_size);

#ifdef __cplusplus
}
#endif

#endif //_GAME_H