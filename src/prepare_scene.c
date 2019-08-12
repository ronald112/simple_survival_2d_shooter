#include "header.h"

void prepare_scene(t_app *app) {
    SDL_SetRenderDrawColor(app->renderer, 51, 0, 0, 255);
    SDL_RenderClear(app->renderer);
}

void present_scene(t_app *app) {
    SDL_RenderPresent(app->renderer);
}

static void init_stage(t_app *app) {
    
}
