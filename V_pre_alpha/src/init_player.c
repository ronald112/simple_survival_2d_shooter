#include "header.h"

void init_player(t_entity *player, t_stage *stage, t_app *app)
{
	stage->entity_head.next = player;
	stage->entity_tail = player;
	
	player->texture = loadTexture("gfx/player.png", app);
	player->health = 5;
	player->x = SCREEN_WIDTH / 2;
	player->y = SCREEN_HEIGHT / 2;
	
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}
