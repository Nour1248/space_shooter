#ifndef _STRUCTS_H
#define _STRUCTS_H 69

#include <SDL2/SDL.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct
{
    SDL_Renderer *renderer;
    SDL_Window *window;
    bool up;
    bool down;
    bool right;
    bool left;
    bool fire;
} App;

typedef struct
{
    SDL_Texture *texture;
    SDL_Rect rect;
    uint8_t hp;
} Entity;

typedef struct
{
    SDL_Texture *texture;
    uint8_t idx;
    uint64_t start;
    uint32_t delay;
    SDL_Rect rect;
} Animation;

typedef struct
{
    SDL_Texture *texture;
    SDL_Rect rect;
} Ui;

#endif //_STRUCTS_H
