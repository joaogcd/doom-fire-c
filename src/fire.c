#include "fire.h"
#include "config.h"
#include "colors.h"

static int fire_pixels[NUM_PIXELS];


void init_fire(void)
{
    for (int i = 0; i < NUM_PIXELS; i++)
        fire_pixels[i] = 0;

    int base = FIRE_WIDTH * (FIRE_HEIGHT - 1);

    for (int col = 0; col < FIRE_WIDTH; col++)
        fire_pixels[base + col] = PALETTE_SIZE - 1; /* 36 */
}

static void update_pixel(int index)
{
    int below = index + FIRE_WIDTH;

    if (below >= NUM_PIXELS)
        return;

    int decay     = rand() % 3;
    int intensity = fire_pixels[below] - decay;
    if (intensity < 0) intensity = 0;

    int target = index - decay;
    if (target >= 0)
        fire_pixels[target] = intensity;
}

void propagate_fire(void)
{
    for (int row = 0; row < FIRE_HEIGHT; row++)
        for (int col = 0; col < FIRE_WIDTH; col++)
            update_pixel(col + FIRE_WIDTH * row);
}

void render_fire(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int row = 0; row < FIRE_HEIGHT; row++) {
        for (int col = 0; col < FIRE_WIDTH; col++) {
            int intensity = fire_pixels[col + FIRE_WIDTH * row];
            const SDL_Color *c = &FIRE_PALETTE[intensity];

            SDL_SetRenderDrawColor(renderer, c->r, c->g, c->b, 255);

            SDL_FRect rect = {
                .x = (float)(col * PIXEL_SIZE),
                .y = (float)(row * PIXEL_SIZE),
                .w = (float)PIXEL_SIZE,
                .h = (float)PIXEL_SIZE
            };
            
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_RenderPresent(renderer);
}
