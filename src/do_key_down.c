#include "header.h"

void doKeyDown(SDL_KeyboardEvent *event, t_app *app)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			app->up = 1;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			app->down = 1;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			app->left = 1;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			app->right = 1;
		}
	}
}
