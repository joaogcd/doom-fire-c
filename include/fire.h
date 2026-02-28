#ifndef _FIRE_C_
#define _FIRE_C_

#include <SDL3/SDL.h>
#include <stdlib.h>
#include <time.h>

void init_fire(void);

static void update_pixel(int index);

void propagate_fire(void);

void render_fire(SDL_Renderer *renderer);

#endif