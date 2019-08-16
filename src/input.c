#include "header.h"


void doKeyUp(SDL_KeyboardEvent *event, t_app *app) {
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
		app->keyboard[event->keysym.scancode] = 0;
	}
	Mix_Pause(7);
}

void doKeyDown(SDL_KeyboardEvent *event, t_app *app) {
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
		app->keyboard[event->keysym.scancode] = 1;
	}
}

void doMouseButtonUp(SDL_MouseButtonEvent *event, t_app *app) {
	app->mouse.button[event->button] = 0;
}

void doMouseButtonDown(SDL_MouseButtonEvent *event, t_app *app) {
	app->mouse.button[event->button] = 1;
}

int do_input(t_app *app, Mix_Chunk *steps_sounds, t_entity *player, t_sounds *sound) {
    SDL_Event event;
    
    while(SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            exit(0);
            break;

        case SDL_KEYDOWN:
			doKeyDown(&event.key, app);

			if ((&event.key)->keysym.scancode == SDL_SCANCODE_ESCAPE)
				return 5;
            
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

        case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&app->mouse.x, &app->mouse.y);
                if ((app->mouse.x >= app->but1.x && app->mouse.x <= app->but1.x + app->but1.w)
                && (app->mouse.y >= app->but1.y && app->mouse.y <= app->but1.y + app->but1.h)) {
                    sound->main_menu_music = Mix_LoadMUS("resource/Audio/Music/ElectroHouse.mp3");
                }
                else if ((app->mouse.x >= app->vol_button.x && app->mouse.x <= app->vol_button.x + app->vol_button.w)
                && (app->mouse.y >= app->vol_button.y && app->mouse.y <= app->vol_button.y + app->vol_button.h)) {
                    set_volume(sound->tmp);
                    set_volume_all_chunks(sound->tmp);
                    sound->tmp *= -1;
                }
			doMouseButtonDown(&event.button, app);
			break;
		
		case SDL_MOUSEBUTTONUP:
			doMouseButtonUp(&event.button, app);
			break;
		
		case SDL_MOUSEWHEEL:
			app->mouse.wheel = event.wheel.y;
			break;

        default:
            break;
        }
    }
    return 0;
}
