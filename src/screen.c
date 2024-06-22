#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

char *fill_char(char t[], int expand){
	int i;
	char *n = (char *)malloc(sizeof(char));
	for(i = 0; t[i] != '\0'; ++i){
		n[i] = t[i];
	}
	if(i < expand)
		for(; i < expand - 1; ++i){
			n[i] = ' ';
		}
	n[i] = '\0';
	return n;
}


void draw_frame(SDL_Renderer *rend, struct BLOCK blocks[], void (*on_hit)(void), void (*on_get)(void), char *header){
	int x, y;

	int i;
	for(i = 0; i < blocks[i].x; ++i){
		// printf("%i\n", i);
		SDL_Rect rect;
		rect.x = blocks[i].x;
		rect.y = blocks[i].y;

		rect.w = rect.h = 30;

		SDL_SetRenderDrawColor(rend, 255, 0, 255, 255);
		SDL_RenderFillRect(rend, &rect);
	}

}

