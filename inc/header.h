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
#include <time.h>

#define PI 3.14159265358979323846
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define FPS 60
#define MAX_KEYBOARD_KEYS 350
#define MAX_MOUSE_BUTTONS   6

#define MAX_ENTITIES 256
#define OBSTACLES_NUM 7
#define SPAWN_SPOTS 3

#define PLAYER_SPEED 6
#define PLAYER_HEALTH 10
#define PLAYER_RADIUS 64

#define ENEMY_SPEED 4
#define ENEMY_HEALTH 2
#define ENEMY_RADIUS 64
#define ENEMY_ATTACK_POWER 3
#define ENEMY_RELOAD 32

#define TEXTURES 4

#define VOLUMESOUND 40
#define VOLUMEMUSIC 20

//#define GLYPH_WIDTH  18
//#define GLYPH_HEIGHT 29

typedef struct s_app t_app;
typedef struct s_entity t_entity;

enum {
    SIDE_NONE,
    SIDE_PLAYER,
    SIDE_ENEMY
};

enum {
    WPN_GUN,
    WPN_AK47,
    WPN_MAX
};

typedef struct s_mouse {
    int x;
    int y;
    int button[MAX_MOUSE_BUTTONS];
    int wheel;
} t_mouse;

struct s_entity {
    int side; 
	float x;
	float y;
    int w;
    int h;
    int radius;
    float dx;
    float dy;
    int health;
    int reload;
    int angle;
    int weapon_type;
    int attack_power;
    int texture_timer;
    int texture_index;
	SDL_Texture *texture;
    SDL_Texture *txtr_walk[TEXTURES];
    SDL_Texture *txtr_fight[TEXTURES];

    void (*targeting)(t_entity *self, t_entity *other);
    void (*attack)(t_entity *self, t_entity *other);
    t_entity *(*touch)(t_entity *self, t_entity **entities);

};

typedef struct s_stage {
    SDL_Texture *targetter_texture;
    SDL_Surface *background_sf;
    SDL_Texture *background_tx;
    SDL_Texture *spawn_spot_tx;
    SDL_Texture *bullet;
    SDL_Texture *enemy_walk[TEXTURES];
    SDL_Texture *enemy_fight[TEXTURES];
    SDL_Texture *obstacles[TEXTURES];

    int ammo[WPN_MAX];
    int enemy_spawn_timer;
} t_stage;

typedef struct s_sounds {
    Mix_Music *main_menu_music;
    Mix_Chunk *cave_background_sounds;
    Mix_Chunk *steps_sounds;
    Mix_Chunk *able_fire_sounds;
    Mix_Chunk *unable_fire_sounds;
    Mix_Chunk *reload_sounds;
    int tmp;
} t_sounds;

typedef struct Delegate {
    void (*logic)(t_app *app, t_stage *stage, t_entity *player, t_entity **entities, t_entity **bullets, int *spwn_xy, t_sounds *sound);
    void (*draw)(t_stage *stage, t_app *app, t_entity **entities, t_entity **bullets, t_entity *player, int *spwn_xy); //
} Delegate;

struct s_app {
    SDL_Renderer *renderer;
    SDL_Window *window;
    struct Delegate delegate;
    int keyboard[MAX_KEYBOARD_KEYS];
    t_mouse mouse;
    SDL_Rect but1;
    SDL_Rect but2;
    SDL_Rect but3;
    SDL_Rect image_fone;
    SDL_Rect img;
    SDL_Rect vol_button;
};

// init block
void set_volume_all_chunks(int i);
void set_volume(int i);
int pick_button(t_app *app, t_sounds *sound);
void create_button(t_app *app);
void init_SDL(t_app *app, t_sounds *sound);
void init_stage(t_stage *stage, t_app *app, t_entity *player, t_entity **bullets);
void init_player(t_entity *player, t_stage *stage, t_app *app, t_entity **entities);
void init_enemies(t_app *app, t_stage *stage);
void init_bullets(t_app *app, t_stage *stage);
void init_containers(t_entity **entities, t_entity **bullets);
void add_enemy(int x, int y, t_stage *stage, t_entity **entities, t_entity *player);
void spawn_enemy(t_stage *stage, t_entity **entities, t_entity *player, int *spwn_xy);
void place_spawn_spots(int *arr);
void cleanup(t_app *app, t_stage *stage, t_entity *button_01, t_entity *button_02
, t_entity *button_03, t_entity *img_fone, t_entity *back_image, t_entity *vol_button);

// draw block
void draw(t_stage *stage, t_app *app, t_entity **entities, t_entity **bullets, t_entity *player, int *spwn_xy);
void draw_menu(t_entity *button_01, t_entity *button_02
, t_entity *button_03, t_entity *vol_on, t_entity *img_fone, t_entity *back_image, t_app *app);
void draw_interface(t_entity *vol_on, t_app *app);
void prepare_scene(t_app *app, SDL_Rect *dest);
void present_scene(t_app *app);
SDL_Texture *loadTexture(char *filename, t_app *app);
void blit(SDL_Texture *texture, int x, int y, int center, t_app *app);
void blit_rotated(SDL_Texture *texture, int x, int y, float angle, t_app *app);
void draw_entities(t_stage *stage, t_app *app, t_entity **entities, int *spwn_xy);
void draw_bullets(t_stage *stage, t_app *app, t_entity **bullets);
//void draw_player(t_app *app, t_entity *player); // // //

// input block
int do_input(t_app *app, Mix_Chunk *steps_sounds, t_entity *player, t_sounds *sound);
void doKeyDown(SDL_KeyboardEvent *event, t_app *app);
void doKeyUp(SDL_KeyboardEvent *event, t_app *app);
void doMouseButtonUp(SDL_MouseButtonEvent *event, t_app *app);
void doMouseButtonDown(SDL_MouseButtonEvent *event, t_app *app);

// logic block
void logic(t_app *app, t_stage *stage, t_entity *player, t_entity **entities, t_entity **bullets, int *spwn_xy, t_sounds *sound);
float get_angle(int x1, int y1, int x2, int y2);
void calc_slope(int x1, int y1, int x2, int y2, float *dx, float *dy);
int get_distance(int x1, int y1, int x2, int y2);
void do_player(t_app *app, t_stage *stage, t_entity *player, t_entity **bullets, t_sounds *sound);
void do_entities(t_stage *stage, t_entity **entities, t_entity *player);
void do_bullets(t_entity **entities, t_entity **bullets, t_sounds *sound);
void fire_bullet(t_app *app, t_stage *stage, t_entity *player, t_entity **bullets, t_sounds *sound);
void fire_AK47(t_app *app, t_stage *stage, t_entity *player, t_entity **bullets, t_sounds *sound);
void fire_gun(t_app *app, t_stage *stage, t_entity *player, t_entity **bullets, t_sounds *sound);
void bullet_hit(t_entity **entities, t_entity *bullet);
t_entity *touch_others(t_entity *self, t_entity **entities);
void do_targeting(t_entity *self, t_entity *other);
void melee_attack(t_entity *self, t_entity *other);
void destroy_entity(t_entity *entity);
void capFrameRate(long *then, float *remainder);

#endif
