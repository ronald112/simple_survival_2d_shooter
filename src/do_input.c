#include "header.h"

void do_input(t_app *app) {
    SDL_Event event;
    SDL_GetMouseState(&app->mouse.x, &app->mouse.y);

    while(SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;
            
        case SDL_KEYDOWN:
			doKeyDown(&event.key, app);
			break;

        case SDL_KEYUP:
			doKeyUp(&event.key, app);
			break;
        
        default:
            break;
        }
    }
}
