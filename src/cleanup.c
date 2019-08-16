#include "header.h"

void cleanup(t_app *app, t_stage *stage, t_entity *button_01, t_entity *button_02
, t_entity *button_03, t_entity *img_fone, t_entity *back_image, t_entity *vol_button) {
	SDL_DestroyTexture(button_01->texture);
	SDL_DestroyTexture(button_02->texture);
	SDL_DestroyTexture(button_03->texture);
	SDL_DestroyTexture(img_fone->texture);
	SDL_DestroyTexture(back_image->texture);
	SDL_DestroyTexture(vol_button->texture);
	SDL_DestroyTexture(stage->background_tx);
    SDL_FreeSurface(stage->background_sf);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
}
