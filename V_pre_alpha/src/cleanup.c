#include "header.h"

void cleanup(t_app *app) {
	SDL_DestroyTexture(app->background_tx);
    SDL_FreeSurface(app->background_sf);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
}
