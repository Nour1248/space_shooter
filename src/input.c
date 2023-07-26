#include <SDL2/SDL.h>

#include "game.h"

void handle_input(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.key.type)
        {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_KEYDOWN:
            handle_keydown(&event.key);
            break;
        case SDL_KEYUP:
            handle_keyup(&event.key);
            break;
        }
    }
}

void handle_keydown(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0)
    {
        switch (event->keysym.scancode)
        {
        case SDL_SCANCODE_UP:
            g_app.up = true;
            break;
        case SDL_SCANCODE_DOWN:
            g_app.down = true;
            break;
        case SDL_SCANCODE_RIGHT:
            g_app.right = true;
            break;
        case SDL_SCANCODE_LEFT:
            g_app.left = true;
            break;
        case SDL_SCANCODE_SPACE:
            g_app.fire = true;
            break;
        default:
            break;
        }
    }
}

void handle_keyup(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0)
    {
        switch (event->keysym.scancode)
        {
        case SDL_SCANCODE_UP:
            g_app.up = false;
            break;
        case SDL_SCANCODE_DOWN:
            g_app.down = false;
            break;
        case SDL_SCANCODE_RIGHT:
            g_app.right = false;
            break;
        case SDL_SCANCODE_LEFT:
            g_app.left = false;
            break;
        case SDL_SCANCODE_SPACE:
            g_app.fire = false;
            break;
        default:
            break;
        }
    }
}