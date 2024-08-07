#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "rules.h"
#include "renderer.h"


void draw_frame(SDL_Renderer *rend, TTF_Font* font, struct BLOCK blocks[], void (*on_hit)(void), char *header){
	int x, y, i;

	rtextf(rend, font, header, FONTSIZ);

	if(blocks[0].y <= 30)
		on_hit();            // top limit
	else if(blocks[0].y >= (Y_SCALE * STEP) + STEP * 2)
		on_hit();            // bottom limit
	else if(blocks[0].x >= (X_SCALE * STEP) + STEP * 2)
		on_hit();            // left limit
	else if(blocks[0].x <= 4)
		on_hit();            // right limit

	// render rects
	for(i = 0; i < blocks[i].x; ++i){
		SDL_Rect rect;
		rect.x = blocks[i].x - STEP;
		rect.y = blocks[i].y - STEP;
		rect.w = rect.h = STEP;

		if(blocks[i].act == A_HEAD)
			SDL_SetRenderDrawColor(rend, GHKLR.r, GHKLR.g, GHKLR.b, 255);
		else if(blocks[i].act == A_POINT)
			SDL_SetRenderDrawColor(rend, GPKLR.r, GPKLR.g, GPKLR.b, GPKLR.a);
		else
			SDL_SetRenderDrawColor(rend, GBKLR.r, GBKLR.g, GBKLR.b, GBKLR.a);

		SDL_RenderFillRect(rend, &rect);

		// draw rect border
		SDL_SetRenderDrawColor(rend, BKLR.r, BKLR.g, BKLR.b, BKLR.a);
		SDL_RenderDrawRect(rend, &rect);
	}
}

