#include "header.h"

void doKeyUp(SDL_KeyboardEvent *event, t_app *app)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_W)
		{
			app->up = 0;
			Mix_Pause(7);

		}
		
		if (event->keysym.scancode == SDL_SCANCODE_S)
		{
			app->down = 0;
			Mix_Pause(7);
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_A)
		{
			app->left = 0;
			Mix_Pause(7);
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_D)
		{
			app->right = 0;
			Mix_Pause(7);
		}
	}
}
