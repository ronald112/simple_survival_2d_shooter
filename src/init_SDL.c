#include "header.h"

void init_SDL(t_app *app) {
    int render_flags = 0;
    render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;   

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    app->window = SDL_CreateWindow("Shooter 01", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
       
    if (!app->window) {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    app->renderer = SDL_CreateRenderer(app->window, -1, render_flags);
    if (!app->renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
    // img не работает
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    //app->background = loadTexture("gfx/background.jpg", app);
      
		
	
    
}
