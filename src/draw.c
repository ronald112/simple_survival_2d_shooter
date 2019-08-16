#include "header.h"

void draw(t_stage *stage, t_app *app, t_entity **entities, t_entity **bullets, t_entity *player, int *spwn_xy) {
	draw_entities(stage, app, entities, spwn_xy);
	//draw_player(app, player);
	draw_bullets(stage, app, bullets);
	
	//draw_hud();
	
	blit(stage->targetter_texture, app->mouse.x, app->mouse.y, 1, app);
}

SDL_Texture *loadTexture(char *filename, t_app *app) {
	SDL_Texture *texture;	

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(app->renderer, filename);

	return texture;
}

void prepare_scene(t_app *app, SDL_Rect *dest) {
    SDL_SetRenderDrawColor(app->renderer, 51, 0, 0, 255);
    SDL_RenderClear(app->renderer);
}

void present_scene(t_app *app) {
    SDL_RenderPresent(app->renderer);
}

void draw_entities(t_stage *stage, t_app *app, t_entity **entities, int *spwn_xy) {
	SDL_RenderCopy(app->renderer, stage->background_tx, NULL, NULL);

    for (int i = 0, j = SPAWN_SPOTS * 2 - 1; i < j; i += 2) {
        blit(stage->spawn_spot_tx, spwn_xy[i], spwn_xy[i+1], 1, app);
    }
    // blit(stage->obstacles[0], 300, 300, 1, app);
    // blit(stage->obstacles[1], 300, 400, 1, app);
    // blit(stage->obstacles[2], 400, 300, 1, app);
    // blit(stage->obstacles[3], 500, 600, 1, app);
	
    for (int i = 0; i < MAX_ENTITIES; i++) {
        t_entity *e = entities[i];

        if (e->health > 0) { // add timer check here
            blit_rotated(e->texture, e->x, e->y, e->angle, app);
        }
    }
}

// void draw_player(t_app *app, t_entity *player) {
// 	blit_rotated(player->texture, player->x, player->y, player->angle, app);
// }


void draw_bullets(t_stage *stage, t_app *app, t_entity **bullets) {
	for (int index = 0; index < MAX_ENTITIES; index++) {
		if (bullets[index]->health > 0)
			blit_rotated(bullets[index]->texture, bullets[index]->x, bullets[index]->y, bullets[index]->angle, app);
	}
}

void blit_rotated(SDL_Texture *texture, int x, int y, float angle, t_app *app) {
	SDL_Rect dst_rect;
	dst_rect.x = x;
	dst_rect.y = y;
	
	SDL_QueryTexture(texture, NULL, NULL, &dst_rect.w, &dst_rect.h);

	dst_rect.x -= (dst_rect.w / 2);
	dst_rect.y -= (dst_rect.h / 2);

	SDL_RenderCopyEx(app->renderer, texture, NULL, &dst_rect, angle, NULL, SDL_FLIP_NONE);
}

void blit(SDL_Texture *texture, int x, int y, int center, t_app *app) {
    SDL_Rect dest;
	
	dest.x = x;
	dest.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	
	if (center) {
		dest.x -= dest.w / 2;
		dest.y -= dest.h / 2;
	}
	SDL_RenderCopy(app->renderer, texture, NULL, &dest);

}

int pick_button(t_app *app, t_sounds *sound) {
    int tmp = -1;
    SDL_Event event;
    while (1) {
        while (SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT)
                exit(0);
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&app->mouse.x, &app->mouse.y);
                if ((app->mouse.x >= app->but1.x && app->mouse.x <= app->but1.x + app->but1.w)
                && (app->mouse.y >= app->but1.y && app->mouse.y <= app->but1.y + app->but1.h)){
                    sound->main_menu_music = Mix_LoadMUS("resource/Audio/Music/ElectroHouse.mp3");
                    Mix_PlayMusic(sound->main_menu_music, -1);
                    return 1;
                }
                else if ((app->mouse.x >= app->but2.x && app->mouse.x <= app->but2.x + app->but2.w)
                && (app->mouse.y >= app->but2.y && app->mouse.y <= app->but2.y + app->but2.h))
                    return 0;
                else if ((app->mouse.x >= app->but3.x && app->mouse.x <= app->but3.x + app->but3.w)
                && (app->mouse.y >= app->but3.y && app->mouse.y <= app->but3.y + app->but3.h))
                    return 3;
                else if ((app->mouse.x >= app->vol_button.x && app->mouse.x <= app->vol_button.x + app->vol_button.w)
                && (app->mouse.y >= app->vol_button.y && app->mouse.y <= app->vol_button.y + app->vol_button.h)){
                    set_volume(tmp);
                    set_volume_all_chunks(tmp);
                    tmp *= -1;
                }
                else
                    return 0;
            }
        }
    }
}

void create_button(t_app *app) {
    app->but1.x = SCREEN_WIDTH / 2 - 192;
    app->but1.y = 200;
    app->but1.h = 90;
    app->but1.w = 384;
    app->but2.x = SCREEN_WIDTH / 2 - 192;
    app->but2.y = 500;
    app->but2.h = 90;
    app->but2.w = 384;
    app->but3.x = SCREEN_WIDTH / 2 - 192;
    app->but3.y = 800;
    app->but3.h = 90;
    app->but3.w = 384;
    app->img.x = 0;
    app->img.y = 0;
    app->img.h = 1080;
    app->img.w = 1920;
    app->image_fone.x = 1300;
    app->image_fone.y = 550;
    app->image_fone.h = 600;
    app->image_fone.w = 600;
    app->vol_button.x = 5;
    app->vol_button.y = 5;
    app->vol_button.h = 52;
    app->vol_button.w = 50;
}

void draw_menu(t_entity *button_01, t_entity *button_02
    , t_entity *button_03, t_entity *vol_on, t_entity *img_fone, t_entity *back_image, t_app *app) {

    // SDL_SetRenderDrawColor(app->renderer, 120, 120, 0, 255);
    // SDL_RenderFillRect(app->renderer, &app->but1);
    // SDL_RenderFillRect(app->renderer, &app->but2);
    // SDL_RenderFillRect(app->renderer, &app->but3);
    SDL_QueryTexture(img_fone->texture, NULL, NULL, &app->img.w, &app->img.h);
    SDL_RenderCopy(app->renderer, img_fone->texture, NULL, &app->img);

    SDL_QueryTexture(back_image->texture, NULL, NULL, &app->image_fone.w, &app->image_fone.h);
    SDL_RenderCopy(app->renderer, back_image->texture, NULL, &app->image_fone);

    SDL_QueryTexture(button_01->texture, NULL, NULL, &app->but1.w, &app->but1.h);
    SDL_RenderCopy(app->renderer, button_01->texture, NULL, &app->but1);    
    SDL_QueryTexture(button_02->texture, NULL, NULL, &app->but2.w, &app->but2.h);
    SDL_RenderCopy(app->renderer, button_02->texture, NULL, &app->but2);    
    SDL_QueryTexture(button_03->texture, NULL, NULL, &app->but3.w, &app->but3.h);
    SDL_RenderCopy(app->renderer, button_03->texture, NULL, &app->but3);
    SDL_QueryTexture(vol_on->texture, NULL, NULL, &app->vol_button.w, &app->vol_button.h);
    SDL_RenderCopy(app->renderer, vol_on->texture, NULL, &app->vol_button);
}

void draw_interface(t_entity *vol_on, t_app *app) {
    SDL_QueryTexture(vol_on->texture, NULL, NULL, &app->vol_button.w, &app->vol_button.h);
    SDL_RenderCopy(app->renderer, vol_on->texture, NULL, &app->vol_button);
}


