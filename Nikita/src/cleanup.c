#include "header.h"

void cleanup(t_app *app) {
	SDL_DestroyRenderer(app->renderer);
	
	SDL_DestroyWindow(app->window);
	
	SDL_Quit();
}
