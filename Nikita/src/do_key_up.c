#include "header.h"

void doKeyUp(SDL_KeyboardEvent *event, t_app *app)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			app->up = 0;
			Mix_Pause(7);
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			app->down = 0;
			Mix_Pause(7);
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			app->left = 0;
			Mix_Pause(7);
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			app->right = 0;
			Mix_Pause(7);
		}
	}
}
