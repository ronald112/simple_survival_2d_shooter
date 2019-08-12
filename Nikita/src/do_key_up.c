#include "header.h"

void doKeyUp(SDL_KeyboardEvent *event, t_app *app)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			Mix_Pause(-1);
			app->up = 0;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			Mix_Pause(-1);
			app->down = 0;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			Mix_Pause(-1);
			app->left = 0;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			Mix_Pause(-1);
			app->right = 0;
		}
	}
}
