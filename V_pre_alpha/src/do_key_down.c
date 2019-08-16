#include "header.h"

void doKeyDown(SDL_KeyboardEvent *event, t_app *app, t_entity *player)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_W)
		{
			app->up = 4;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_S)
		{
			app->down = 4;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_A)
		{
			app->left = 4;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_D)
		{
			app->right = 4;
		}		
	}
	
}
