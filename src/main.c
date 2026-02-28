#include <SDL3/SDL.h>
#include <stdio.h>

#include "config.h"
#include "colors.h"
#include "fire.h"


int main(void)
{
    srand((unsigned)time(NULL));

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        WINDOW_TITLE,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        0
    );
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        fprintf(stderr, "SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    init_fire();

    const Uint64 FRAME_MS = 1000 / 30; /* 30 FPS */
    SDL_Event event;
    Uint64 last_tick = SDL_GetTicks();

    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                return 0;
            if (event.type == SDL_EVENT_KEY_DOWN &&
                event.key.key == SDLK_ESCAPE)
                return 0;
        }


        Uint64 now = SDL_GetTicks();

        if (now - last_tick >= FRAME_MS) {
            propagate_fire();
            render_fire(renderer);
            last_tick = now;
        }

        SDL_Delay(1);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}