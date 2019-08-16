#include "header.h"

void prepare_scene(t_app *app, SDL_Rect *dest) {
    SDL_SetRenderDrawColor(app->renderer, 51, 0, 0, 255);
    SDL_RenderClear(app->renderer);
}

void present_scene(t_app *app) {
    SDL_RenderPresent(app->renderer);
}

void init_stage(t_entity *player, t_stage *stage, t_app *app) {
    SDL_Texture *targetterTexture;
    //targetterTexture = loadTexture("gfx/targetter.png", app);

    stage->entity_tail = &stage->entity_head;
    init_player(player, stage, app);
}

void logic(t_stage *stage, t_entity *player, t_app *app) {
    player->angle = get_angle(player->x, player->y, app->mouse.x, app->mouse.y);

    do_entities(stage, player);
}

void draw(t_entity *player, t_stage *stage, t_app *app) {
    //blit(player->texture, player->x, player->y, app);
    draw_entities(stage, app);
}

