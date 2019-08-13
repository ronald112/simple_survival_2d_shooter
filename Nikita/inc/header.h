#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>

#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

typedef struct s_mouse {
    int x;
    int y;
} t_mouse;

typedef struct s_app{
    SDL_Renderer *renderer;
    SDL_Window *window;
    int *background;
    // SDL_Texture *texture_app;

    int up;
	int down;
	int left;
	int right;

    t_mouse mouse;
} t_app;

typedef struct s_entity{
	int x;
	int y;
	SDL_Texture *texture;
} t_entity;

static void init_stage(t_app *app);
void init_SDL(t_app *app);
void do_input(t_app *app, Mix_Chunk *steps_sounds);
void cleanup(t_app *app);

// подготовка мапы и загрузка текстур
//void prepare_scene(t_app *app);
void prepare_scene(t_app *app, SDL_Rect *dest);
void present_scene(t_app *app);
SDL_Texture *loadTexture(char *filename, t_app *app);
void blit(SDL_Texture *texture, int x, int y, t_app *app);

// движения героя
void doKeyDown(SDL_KeyboardEvent *event, t_app *app);
void doKeyUp(SDL_KeyboardEvent *event, t_app *app);




#endif


