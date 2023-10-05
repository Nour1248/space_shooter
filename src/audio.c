#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"

void
init_audio ()
{
  if (Mix_OpenAudio (MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 3, 1024) != 0)
    {
      fprintf (stderr, "FAILED TO OPEN AUDIO DUE TO : %s", Mix_GetError ());
      exit (EXIT_FAILURE);
    }

  g_pewpewChunk = Mix_LoadWAV ("assets/sounds/pew.wav");
  g_boomChunk = Mix_LoadWAV ("assets/sounds/expl6.wav");
  g_uiMusic
      = Mix_LoadMUS ("assets/sounds/tgfcoder-FrozenJam-SeamlessLoop.ogg");
}

//
Mix_Chunk *g_pewpewChunk;

void
pewpew ()
{
  Mix_PlayChannel (-1, g_pewpewChunk, 0);
}

//
Mix_Chunk *g_boomChunk;

//
void
boom ()
{
  Mix_PlayChannel (-1, g_boomChunk, 0);
}

//
Mix_Music *g_uiMusic;

//
void
play_uiMusic ()
{
  Mix_PlayMusic (g_uiMusic, 1);
}