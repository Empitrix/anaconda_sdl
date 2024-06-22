#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include "control.h"
#include "utils.h"
#include "rules.h"


volatile int status = 0;
static void (*p_event)(enum DIRECTION);


void loop_event(int width, int height, void (*eloop)(SDL_Renderer*)) {

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		printf("Failed: %s\n", SDL_GetError());
	}

	SDL_Window* win = SDL_CreateWindow("Anaconda",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, 0);

	SDL_Renderer* rend = SDL_CreateRenderer(
		win, -1, SDL_RENDERER_ACCELERATED);

	// FONT
	TTF_Init();
	TTF_Font *font = TTF_OpenFont("./assets/poppins.ttf", 20);


	if(font == NULL)
		printf("TTF Failed: %s\n", TTF_GetError());


	while(running){

		SDL_SetRenderDrawColor(rend, 30, 30, 30, 255);
		SDL_RenderClear(rend);

		SDL_Event event;

		getdir(event);  // update direction 
		eloop(rend);

		SDL_RenderPresent(rend);

		SDL_Delay(game_speed);  // 60 FPS
	}

	SDL_DestroyWindow(win);
	SDL_Quit();
}

