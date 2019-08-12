#include "header.h"

void doKeyDown(SDL_KeyboardEvent *event, t_app *app, Mix_Chunk *steps_sounds)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			Mix_PlayChannel(-1, steps_sounds, -1);
			app->up = 1;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			Mix_PlayChannel(-1, steps_sounds, -1);
			app->down = 1;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			Mix_PlayChannel(-1, steps_sounds, -1);
			app->left = 1;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			Mix_PlayChannel(-1, steps_sounds, -1);
			app->right = 1;
		}
	}
}
