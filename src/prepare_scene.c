#include "header.h"

void prepare_scene(t_app *app, SDL_Rect *dest) {
    SDL_SetRenderDrawColor(app->renderer, 51, 0, 0, 255);
    //SDL_RenderCopy(app->renderer, app->background, NULL, dest);
    SDL_RenderClear(app->renderer);
}

void present_scene(t_app *app) {
    SDL_RenderPresent(app->renderer);
}

static void init_stage(t_app *app) {
    
}
