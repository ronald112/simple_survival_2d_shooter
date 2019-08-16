#include "header.h"

void set_volume_all_chunks(int i) {
    if(i == 1)
        Mix_Volume(-1, VOLUMESOUND);
    else Mix_Volume(-1, 0);
}
void set_volume(int i) {
    if(i == 1) Mix_VolumeMusic(VOLUMEMUSIC);
    else Mix_VolumeMusic(0);
}

void logic(t_app *app, t_stage *stage, t_entity *player, t_entity **entities, t_entity **bullets, int *spwn_xy, t_sounds *sound) {
    do_player(app, stage, player, bullets, sound);
    do_entities(stage, entities, player);
    do_bullets(entities, bullets, sound);
    spawn_enemy(stage, entities, player, spwn_xy);
}

void do_player(t_app *app, t_stage *stage, t_entity *player, t_entity **bullets, t_sounds *sound) {
    player->dx *= 0.5;
    player->dy *= 0.5;

    if (app->keyboard[SDL_SCANCODE_W]) {
        player->dy = -PLAYER_SPEED;
    }

    if (app->keyboard[SDL_SCANCODE_S]) {
        player->dy = PLAYER_SPEED;
    }

    if (app->keyboard[SDL_SCANCODE_A]) {
        player->dx = -PLAYER_SPEED;
    }

    if (app->keyboard[SDL_SCANCODE_D]) {
        player->dx = PLAYER_SPEED;
    }

    player->angle = get_angle(player->x, player->y, app->mouse.x, app->mouse.y);
    
    if (player->reload == 0 && stage->ammo[player->weapon_type] > 0 && app->mouse.button[SDL_BUTTON_LEFT]) {
        fire_bullet(app, stage, player, bullets, sound);
        stage->ammo[player->weapon_type]--;
        Mix_PlayChannel(5, sound->able_fire_sounds, 0);
    } 
    else if (player->reload == 0 && app->mouse.button[SDL_BUTTON_LEFT]) {
        Mix_PlayChannel(5, sound->unable_fire_sounds, 0);
        player->reload = 16;
    }
    
    if (app->mouse.wheel < 0) {
        if (--player->weapon_type < WPN_GUN) {
            player->weapon_type = WPN_MAX - 1;
        }
        app->mouse.wheel = 0;
    }
    
    if (app->mouse.wheel > 0) {
        if (++player->weapon_type >= WPN_MAX) {
            player->weapon_type = WPN_GUN;
        }
        app->mouse.wheel = 0;
    }
    
    if (app->mouse.button[SDL_BUTTON_RIGHT]) {
        if (player->weapon_type == WPN_GUN && stage->ammo[WPN_GUN] == 0) {
            stage->ammo[WPN_GUN] = 8;
        }
        if (player->weapon_type == WPN_AK47 && stage->ammo[WPN_AK47] == 0) { 
            stage->ammo[WPN_AK47] = 30;
        }
        Mix_PlayChannel(5, sound->reload_sounds, 0);
        app->mouse.button[SDL_BUTTON_RIGHT] = 0;
    }
}

void do_entities(t_stage *stage, t_entity **entities, t_entity *player) {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        t_entity *e = entities[i];
        if (e->side != SIDE_NONE) {
            
            if (e->targeting != NULL && e != player) {
                e->targeting(e, player);
            }

            if (e->dx != 0 && e->dy != 0 && --e->texture_timer <= 0) {
                ++e->texture_index;
                e->texture_index %= TEXTURES;
                e->texture = e->txtr_walk[e->texture_index];
                e->texture_timer = FPS / 6;
            }

            e->x += e->dx;
            e->y += e->dy;
            
            if (e == player) {
                e->x = MIN(MAX(e->x, e->w / 2), SCREEN_WIDTH - e->w / 2);
                e->y = MIN(MAX(e->y, e->h / 2), SCREEN_HEIGHT - e->h / 2);
            }

            if (e->touch != NULL) {
                t_entity *other = e->touch(e, entities);

                if (other != NULL && e->attack != NULL && e->side != other->side && other->side != SIDE_NONE && other->health > 0 && e->reload == 0) {
                    e->attack(e, other);
                    e->reload = ENEMY_RELOAD;
                }
            }

            e->reload = MAX(e->reload - 1, 0);

            if (e->health <= 0) {
                destroy_entity(e);
            }
        }
    }
}

void do_bullets(t_entity **entities, t_entity **bullets, t_sounds *sound) {
    for (int index = 0; index < MAX_ENTITIES; index++) {
        t_entity *b = bullets[index];

        if (b->health > 0) { 
            b->x += b->dx;
            b->y += b->dy;
        
            if (b->x < 0 || b->x > SCREEN_WIDTH || b->y < 0 || b->y > SCREEN_HEIGHT) {
                destroy_entity(b);
            }
            bullet_hit(entities, b);
        }
    }
}

void fire_bullet(t_app *app, t_stage *stage, t_entity *player, t_entity **bullets, t_sounds *sound) {
    switch (player->weapon_type) {
        case WPN_AK47:
            fire_AK47(app, stage, player, bullets, sound);
            break;
            
        default:
            fire_gun(app, stage, player, bullets, sound);
            break;
    }
}

void fire_AK47(t_app *app, t_stage *stage, t_entity *player, t_entity **bullets, t_sounds *sound) {
    int min_index = -1;

    for (int i = 0; i < MAX_ENTITIES && min_index != 0; i++) {
        if (bullets[i]->health == 0) {
            min_index = i;
            break;
        }
    }
    bullets[min_index]->side = player->side;
    bullets[min_index]->x = player->x;
    bullets[min_index]->y = player->y;
    bullets[min_index]->texture = stage->bullet;
    bullets[min_index]->health = 1;
    bullets[min_index]->angle = player->angle;
    
    calc_slope(app->mouse.x, app->mouse.y, bullets[min_index]->x, bullets[min_index]->y, &bullets[min_index]->dx, &bullets[min_index]->dy);
    
    bullets[min_index]->dx *= 32;
    bullets[min_index]->dy *= 32;
    
    player->reload = 8;
}

void fire_gun(t_app *app, t_stage *stage, t_entity *player, t_entity **bullets, t_sounds *sound) {
    int min_index = -1;

    for (int i = 0; i < MAX_ENTITIES && min_index != 0; i++) {
        if (bullets[i]->health == 0) {
            min_index = i;
            break;
        }
    }
    bullets[min_index]->side = player->side;
    bullets[min_index]->x = player->x;
    bullets[min_index]->y = player->y;
    bullets[min_index]->texture = stage->bullet;
    bullets[min_index]->health = 1;
    bullets[min_index]->angle = player->angle;

    calc_slope(app->mouse.x, app->mouse.y, bullets[min_index]->x, bullets[min_index]->y, &bullets[min_index]->dx, &bullets[min_index]->dy);
    
    bullets[min_index]->dx *= 32;
    bullets[min_index]->dy *= 32;
    
    player->reload = 32;
}

void bullet_hit(t_entity **entities, t_entity *bullet) {
    int dist = 0;
    int hit = 0;

    for (int i = 0; i < MAX_ENTITIES && !hit; i++) {
        t_entity *e = entities[i];

        if (e->side != SIDE_NONE && e->side != bullet->side) {
            dist = get_distance(bullet->x, bullet->y, e->x, e->y);

            if (dist < e->radius + bullet->radius) {
                hit = 1;
                destroy_entity(bullet);
                entities[i]->health--;
            }
        }
    }

}

t_entity *touch_others(t_entity *self, t_entity **entities) {
    int is_touched = 0;
    t_entity *touched = NULL;

    for (int i = 0; i < MAX_ENTITIES && !is_touched; i++) {
        t_entity *e = entities[i];
        int dist = get_distance(self->x, self->y, e->x, e->y);

        if (dist < self->radius + e->radius && e != self) {
            touched = e;
            is_touched = 1;
        }
    }
    return touched;
}

void melee_attack(t_entity *self, t_entity *other) {
    if (other == NULL || self == NULL) return;
    
    other->health -= self->attack_power;
}

void do_targeting(t_entity *self, t_entity *other) {
    int dist = get_distance(self->x, self->y, other->x, other->y);
    self->angle = get_angle(self->x, self->y, other->x, other->y);
    
    calc_slope(other->x, other->y, self->x, self->y, &self->dx, &self->dy);
    if (dist > self->radius + other->radius) {
        self->dx *= ENEMY_SPEED;
        self->dy *= ENEMY_SPEED;
    } else {
        self->dx = 0;
        self->dy = 0;
    }
}

void destroy_entity(t_entity *entity) {
    entity->side = 0;
    entity->x = 0;
    entity->y = 0;
    entity->dx = 0;
    entity->dy = 0;
    entity->radius = 0;
    entity->w = 0;
    entity->h = 0;
    entity->health = 0;
    entity->reload = 0;
    entity->angle = 0;
    entity->weapon_type = 0;
    entity->attack_power = 0;
    entity->texture = NULL;
    entity->targeting = NULL;
    entity->attack = NULL;
    entity->touch = NULL;
}

float get_angle(int x1, int y1, int x2, int y2) {
	float angle = -90 + atan2(y1 - y2, x1 - x2) * (180 / PI);
	
    return angle >= 0 ? angle : 360 + angle;
}

void calc_slope(int x1, int y1, int x2, int y2, float *dx, float *dy) {
    int steps = MAX(abs(x1 - x2), abs(y1 - y2));

    if (steps == 0) {
        *dx = *dy = 0;
        
        return;
    }

    *dx = (x1 - x2);
    *dx /= steps;

    *dy = (y1 - y2);
    *dy /= steps;
}

int get_distance(int x1, int y1, int x2, int y2) {
    int x, y;

    x = x2 - x1;
    y = y2 - y1;

    return sqrt(x * x + y *y);
}

void capFrameRate(long *then, float *remainder) {
    long wait, frameTime;
    
    wait = 16 + *remainder;
    
    *remainder -= (int)*remainder;
    
    frameTime = SDL_GetTicks() - *then;
    
    wait -= frameTime;
    
    if (wait < 1) {
        wait = 1;
    }
        
    SDL_Delay(wait);
    
    *remainder += 0.667;
    
    *then = SDL_GetTicks();
}
