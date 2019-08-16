#include "header.h"

void do_entities(t_stage *stage, t_entity *player) {
    t_entity *e;

    for (e = stage->entity_head.next; e != NULL; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;

        if (e == player) {
            e->x = MIN(MAX(e->x, e->w / 2), SCREEN_WIDTH - e->w / 2);
            e->y = MIN(MAX(e->y, e->h / 2), SCREEN_HEIGHT - e->h / 2);
        }
    }
}

void draw_entities(t_stage *stage, t_app *app) {
	t_entity *e;
	
    SDL_RenderCopy(app->renderer, app->background_tx, NULL, NULL);
	for (e = stage->entity_head.next ; e != NULL ; e = e->next) {
		blit_rotated(e->texture, e->x, e->y, e->angle, app);
	}
}



