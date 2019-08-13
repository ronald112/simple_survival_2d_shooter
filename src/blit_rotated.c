#include "header.h"

void blit_rotated(SDL_Texture *texture, int x, int y, float angle, t_app *app) {
	SDL_Rect dst_rect;

	dst_rect.x = x;
	dst_rect.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dst_rect.w, &dst_rect.h);
	dst_rect.x -= (dst_rect.w / 2);
	dst_rect.y -= (dst_rect.h / 2);

	SDL_RenderCopyEx(app->renderer, texture, NULL, &dst_rect, angle, NULL, SDL_FLIP_NONE);
}
