#include "header.h"

void do_input(t_app *app, Mix_Chunk *steps_sounds) {
	SDL_Event event;
	SDL_GetMouseState(&app->mouse.x, &app->mouse.y);

	while(SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			exit(0);
			break;
			
		case SDL_KEYDOWN:
		{
			doKeyDown(&event.key, app);
			if( (&event.key)->keysym.scancode == SDL_SCANCODE_UP || 
				(&event.key)->keysym.scancode == SDL_SCANCODE_DOWN ||
				(&event.key)->keysym.scancode == SDL_SCANCODE_LEFT ||
				(&event.key)->keysym.scancode == SDL_SCANCODE_RIGHT )
			{
				if(!Mix_Playing(7)) 
					Mix_PlayChannel(7, steps_sounds, 1);
				else {
					Mix_Resume(7);
					if(!Mix_Playing(7)) 
						Mix_PlayChannel(7, steps_sounds, 1);
				}	
			}
					
		}
			
			break;

		case SDL_KEYUP:
		{
			doKeyUp(&event.key, app);
			Mix_Pause(7);
		}
			
			break;
		
		default:
			break;
		}
	}
}
