#include "header.h"

void init_SDL(t_app *app, t_sounds *sound) {
    int render_flags = 0;
    render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;   

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    app->window = SDL_CreateWindow("endgame", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
       
    if (!app->window) {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);  
    sound->main_menu_music = Mix_LoadMUS("resource/Audio/Music/MainMenuTheme.mp3");
    sound->cave_background_sounds = Mix_LoadWAV("resource/Audio/Sounds/Background/Cave.wav");
    sound->steps_sounds = Mix_LoadWAV("resource/Audio/Sounds/Character/Footsteps.wav");
    sound->unable_fire_sounds = Mix_LoadWAV("resource/Audio/Sounds/Wepons/Pistol/cant_fire.wav");
    sound->able_fire_sounds = Mix_LoadWAV("resource/Audio/Sounds/Wepons/Pistol/pistol.wav");
    sound->reload_sounds = Mix_LoadWAV("resource/Audio/Sounds/Wepons/Pistol/reload.wav");
    sound->tmp = -1;
    
    Mix_PlayMusic(sound->main_menu_music, -1);
    set_volume(1);
    set_volume_all_chunks(1);

    //Mix_PlayChannel(6, cave_background_sounds, -1);
    Mix_VolumeChunk(sound->cave_background_sounds, VOLUMESOUND);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    app->renderer = SDL_CreateRenderer(app->window, -1, render_flags);
    if (!app->renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    
    //SDL_ShowCursor(0);
}

void init_stage(t_stage *stage, t_app *app, t_entity *player, t_entity **entities) {
    app->delegate.logic = logic;
    app->delegate.draw = draw;
    
    stage->background_sf = SDL_LoadBMP("gfx/background.bmp");
    stage->background_tx = SDL_CreateTextureFromSurface(app->renderer, stage->background_sf);
    stage->targetter_texture = loadTexture("gfx/targetter.png", app);
    stage->spawn_spot_tx = loadTexture("gfx/spawn_spot.png", app);
    stage->obstacles[0] = loadTexture("gfx/tree-1.png", app);
    stage->obstacles[1] = loadTexture("gfx/tree-2.png", app);
    stage->obstacles[2] = loadTexture("gfx/tree-3.png", app);
    stage->obstacles[3] = loadTexture("gfx/tree-4.png", app);

    init_player(player, stage, app, entities);
    init_enemies(app, stage);
}


void init_player(t_entity *player, t_stage *stage, t_app *app, t_entity **entities) {
    stage->ammo[WPN_GUN] = 8;
    stage->ammo[WPN_AK47] = 30;

    player->side = SIDE_PLAYER;
    player->texture_timer = 0;
    player->texture_index = 0;
    player->txtr_walk[0] = loadTexture("gfx/player-1.png", app);
    player->txtr_walk[1] = loadTexture("gfx/player-2.png", app);
    player->txtr_walk[2] = loadTexture("gfx/player-3.png", app);
    player->txtr_walk[3] = loadTexture("gfx/player-4.png", app);
    player->texture = player->txtr_walk[0];
    player->x = SCREEN_WIDTH / 2;
    player->y = SCREEN_HEIGHT / 2;
    player->dx = 0;
    player->dy = 0;
    player->radius = PLAYER_RADIUS;
    player->health = PLAYER_HEALTH;
    player->reload = 0;
    player->angle = 0;
    player->weapon_type = WPN_GUN;
    player->attack_power = 0;
    player->targeting = NULL;
    player->attack = NULL;
    player->touch = NULL;

    entities[0] = player;
    
    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

void init_bullets(t_app *app, t_stage *stage) {
    stage->bullet = loadTexture("gfx/player_bullet.png", app);
}

void init_enemies(t_app *app, t_stage *stage) {
    stage->enemy_walk[0] = loadTexture("gfx/enemy-1.png", app);
    stage->enemy_walk[1] = loadTexture("gfx/enemy-2.png", app);
    stage->enemy_walk[2] = loadTexture("gfx/enemy-3.png", app);
    stage->enemy_walk[3] = loadTexture("gfx/enemy-4.png", app);

    // stage->enemy_fight[0] = loadTexture("gfx/enemy-1.png", app);
    // stage->enemy_fight[1] = loadTexture("gfx/enemy-2.png", app);
    // stage->enemy_fight[2] = loadTexture("gfx/enemy-3.png", app);
    // stage->enemy_fight[3] = loadTexture("gfx/enemy-4.png", app);
}

void init_containers(t_entity **entities, t_entity **bullets) {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        bullets[i] = (t_entity *)malloc(sizeof(t_entity));
        entities[i] = (t_entity *)malloc(sizeof(t_entity));
        
        bullets[i]->side = entities[i]->side = 0;
        bullets[i]->x = entities[i]->x = 0;
        bullets[i]->y = entities[i]->y = 0;
        bullets[i]->dx = entities[i]->dx = 0;
        bullets[i]->dy = entities[i]->dy = 0;
        bullets[i]->radius = entities[i]->radius = 0;
        bullets[i]->w = entities[i]->w = 0;
        bullets[i]->h = entities[i]->h = 0;
        bullets[i]->health = entities[i]->health = 0;
        bullets[i]->reload = entities[i]->reload = 0;
        bullets[i]->angle = entities[i]->angle = 0;
        bullets[i]->weapon_type = entities[i]->weapon_type = 0;
        bullets[i]->attack_power = entities[i]->attack_power = 0;
        
        bullets[i]->targeting = entities[i]->targeting = NULL;
        bullets[i]->attack = entities[i]->attack = NULL;
        bullets[i]->touch = entities[i]->touch = NULL;
        bullets[i]->texture = entities[i]->texture = NULL;
        bullets[i]->texture_timer = entities[i]->texture_timer = 0;
        bullets[i]->texture_index = entities[i]->texture_index = 0;

        for (int j = 0; j < TEXTURES; j++) {
            bullets[i]->txtr_walk[j] = NULL;
            bullets[i]->txtr_fight[j] = NULL;
            entities[i]->txtr_walk[j] = NULL;
            entities[i]->txtr_fight[j] = NULL;
        }
    }
}

void add_enemy(int x, int y, t_stage *stage, t_entity **entities, t_entity *player) {
    int min_index = -1;

    for (int i = OBSTACLES_NUM; i < MAX_ENTITIES && min_index != 0; i++) {
        if (entities[i]->health == 0) { // add timer-check after
            min_index = i;
            break;
        }
    }
    entities[min_index]->side = SIDE_ENEMY;
    entities[min_index]->texture_timer = 0;
    entities[min_index]->texture_index = 0;
    entities[min_index]->txtr_walk[0] = stage->enemy_walk[0];
    entities[min_index]->txtr_walk[1] = stage->enemy_walk[1];
    entities[min_index]->txtr_walk[2] = stage->enemy_walk[2];
    entities[min_index]->txtr_walk[3] = stage->enemy_walk[3];

    // entities[min_index]->txtr_fight[0] = stage->enemy_fight[0];
    // entities[min_index]->txtr_fight[1] = stage->enemy_fight[1];
    // entities[min_index]->txtr_fight[2] = stage->enemy_fight[2];
    // entities[min_index]->txtr_fight[3] = stage->enemy_fight[3];

    entities[min_index]->x = x;
    entities[min_index]->y = y;
    entities[min_index]->texture = entities[min_index]->txtr_walk[0];
    entities[min_index]->health = ENEMY_HEALTH;
    entities[min_index]->radius = ENEMY_RADIUS;
    entities[min_index]->angle = get_angle(entities[min_index]->x, entities[min_index]->y, player->x, player->y);
    entities[min_index]->attack_power = ENEMY_ATTACK_POWER;
    entities[min_index]->targeting = do_targeting;
    entities[min_index]->attack = melee_attack;
    entities[min_index]->touch = touch_others;
    player->texture_timer = FPS / 6;
    player->texture_index = 0;


    calc_slope(player->x, player->y, entities[min_index]->x, entities[min_index]->y, &entities[min_index]->dx, &entities[min_index]->dy);
    
    entities[min_index]->dx *= ENEMY_SPEED;
    entities[min_index]->dy *= ENEMY_SPEED;
}

void spawn_enemy(t_stage *stage, t_entity **entities, t_entity *player, int *spwn_xy) {
    int x, y;
    int spawn_spot_index = 0;
    
    if (--stage->enemy_spawn_timer <= 0) {

        // add random spawn spot here;
        spawn_spot_index = rand() % SPAWN_SPOTS;

        x = spwn_xy[2*spawn_spot_index];
        y = spwn_xy[2*spawn_spot_index+1];
        
        add_enemy(x, y, stage, entities, player);
        
        stage->enemy_spawn_timer = FPS + (rand() % FPS);
    }
}
void place_spawn_spots(int *arr) {
    for (int i = 0, j = SPAWN_SPOTS * 2 - 1; i < j; i += 2) {
        arr[i] = 100 + rand() % (SCREEN_WIDTH - 200);
        arr[i+1] = 100 + rand() % (SCREEN_HEIGHT - 200);
    }
}
