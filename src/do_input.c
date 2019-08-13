#include "header.h"

void do_input(t_app *app, Mix_Chunk *steps_sounds, t_entity *player) {
    SDL_Event event;
    

    while(SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;
            
        case SDL_KEYDOWN:
			doKeyDown(&event.key, app, player);

            
			if( (&event.key)->keysym.scancode == SDL_SCANCODE_W || 
				(&event.key)->keysym.scancode == SDL_SCANCODE_S ||
				(&event.key)->keysym.scancode == SDL_SCANCODE_A ||
				(&event.key)->keysym.scancode == SDL_SCANCODE_D )
			{
				if(!Mix_Playing(7)) 
					Mix_PlayChannel(7, steps_sounds, 1);
				else {
					Mix_Resume(7);
				if(!Mix_Playing(7)) 
					Mix_PlayChannel(7, steps_sounds, 1);
				}	
			}


			break;

        case SDL_KEYUP:
			doKeyUp(&event.key, app);
            Mix_Pause(7);
			break;
        
        default:
            break;
        }
    }
	
}
