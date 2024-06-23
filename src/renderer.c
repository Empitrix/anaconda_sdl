#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "rules.h"
#include "control.h"

SDL_Renderer *rtextf(SDL_Renderer *rend, TTF_Font* font, char* text, int size){
	int w = (int)strlen(text) * (size) - 100;
	SDL_Surface *txtrend = TTF_RenderText_Blended_Wrapped(font, text, SDL_WKLR, w);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, txtrend);
	SDL_Rect srect = {0, 0, w, TOPSIZ};
	SDL_RenderCopy(rend, texture, NULL, &srect);
	SDL_SetRenderDrawColor(rend, SDL_WKLR.r, SDL_WKLR.g, SDL_WKLR.b, SDL_WKLR.a);
	SDL_RenderDrawLine(rend, 0, TOPSIZ, (STEP * X_SCALE) + STEP, TOPSIZ);
	return rend;
}


void rtextf_rect(SDL_Renderer *rend, TTF_Font* font, char* text, int size, SDL_Rect rect){
	int w = (int)strlen(text) * (size);
	SDL_Surface *txtrend = TTF_RenderText_Blended_Wrapped(font, text, SDL_WKLR, w);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, txtrend);
	SDL_RenderCopy(rend, texture, NULL, &rect);
	SDL_SetRenderDrawColor(rend, SDL_WKLR.r, SDL_WKLR.g, SDL_WKLR.b, SDL_WKLR.a);
}


void gof_rend(SDL_Renderer *rend, TTF_Font* font, int score, void (*restart)(void)){
	SDL_SetRenderDrawColor(rend, BGKLR.r, BGKLR.g, BGKLR.b, BGKLR.a);
	SDL_RenderClear(rend);

	int wi = ((X_SCALE * STEP) + STEP) / 3;
	rtextf_rect(rend, font, "GAME OVER", 80, (SDL_Rect){wi, 20, wi, 80});

	char points[10];
	sprintf(points, "%d ", score);
	int w = (int)strlen(points) * (20);
	rtextf_rect(rend, font, points, 20, (SDL_Rect){wi, 100, w, 80});


	char msg[] = "Press [Y] if you want to play again";
	int tw = (int)strlen(msg) * (20);
	rtextf_rect(rend, font, msg, 10, (SDL_Rect){25, 180, tw, 40});
	SDL_Event event;
	
	int ans = getans(event);

	if(ans != -1){
		if(ans)
			restart();
		else{
			running = 0;
			gofa = 0;
		}
	}
	SDL_RenderPresent(rend);
}

