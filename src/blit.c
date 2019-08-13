#include "header.h"

void blit(SDL_Texture *texture, int x, int y, t_app *app) {
	SDL_Rect dest;
	
	dest.x = x;
	dest.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    // display background
    SDL_RenderCopy(app->renderer, app->background_tx, NULL, NULL);
    // display player
    SDL_RenderCopy(app->renderer, texture, NULL, &dest);

}



