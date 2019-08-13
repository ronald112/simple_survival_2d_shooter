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

#define PI 3.14159265358979323846
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct s_mouse {
    int x;
    int y;
} t_mouse;

typedef struct s_app{
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Surface *background_sf;
    SDL_Texture *background_tx;
    int up;
	int down;
	int left;
	int right;
    t_mouse mouse;
} t_app;

// player
typedef struct s_entity{ 
	float x;
	float y;
    int w;
    int h;
    float dx;
    float dy;
    int health;
    int angle;
	SDL_Texture *texture;
    struct s_entity *next;
} t_entity;

// Stage
typedef struct s_stage {
    t_entity entity_head, *entity_tail;
}t_stage;

typedef struct s_sounds {
    Mix_Music *main_menu_music;
    Mix_Chunk *cave_background_sounds;
    Mix_Chunk *steps_sounds;
}t_sounds;

void init_stage(t_entity *player, t_stage *stage, t_app *app);
void init_SDL(t_app *app);
void do_input(t_app *app, Mix_Chunk *steps_sounds, t_entity *player);
void cleanup(t_app *app);

// подготовка мапы и загрузка текстур
//void prepare_scene(t_app *app);
void prepare_scene(t_app *app, SDL_Rect *dest);
void present_scene(t_app *app);
SDL_Texture *loadTexture(char *filename, t_app *app);
void blit(SDL_Texture *texture, int x, int y, t_app *app);

// движения героя
void doKeyDown(SDL_KeyboardEvent *event, t_app *app, t_entity *player);
void doKeyUp(SDL_KeyboardEvent *event, t_app *app);

// поворот за мишью
float get_angle(int x1, int y1, int x2, int y2);
void blit_rotated(SDL_Texture *texture, int x, int y, float angle, t_app *app);
void draw_entities(t_stage *stage, t_app *app);
void do_entities(t_stage *stage, t_entity *player);
void logic(t_stage *stage, t_entity *player, t_app *app);
void draw(t_entity *player, t_stage *stage, t_app *app);
void init_player(t_entity *player, t_stage *stage, t_app *app);




#endif


