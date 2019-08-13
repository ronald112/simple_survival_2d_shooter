#include "header.h"

void doKeyDown(SDL_KeyboardEvent *event, t_app *app)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_W)
		{
			app->up = 1;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_S)
		{
			app->down = 1;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_A)
		{
			app->left = 1;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_D)
		{
			app->right = 1;
		}
	}
}
