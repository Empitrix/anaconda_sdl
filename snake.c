#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdarg.h>
#include "src/rules.h"
#include "src/screen.h"
#include "src/loop.h"
#include "src/utils.h"


// macros
#define MAXBLOCKS 10000


static int ix, iy = 0;
volatile int points = 0;


void restart();


void gof(SDL_Renderer *rend, TTF_Font* font, int score, char *format, ...){
	char message[1000];
	va_list aptr;
	int ret;
	va_start(aptr, format);
	ret = vsprintf(message, format, aptr);
	va_end(aptr);
	printf("Point%s: %i\n", points <= 1 ? "" : "s", points);
	printf("%s\n", message);


	while(gofa){
		gof_rend(rend, font, points, restart);
		SDL_Delay(100);
	}

	// running = 0;
}

void on_hit(void){
	// running = 0;
	gofa = 1;
}

static int width, height;


static int lvl = 1;
static struct BLOCK blocks[MAXBLOCKS] = {
	{STEP * 10, STEP * 7, A_HEAD},
	{STEP * 10, STEP * 8, A_BODY},
	{STEP * 10, STEP * 9, A_BODY},

	// {STEP * 3, STEP * 2, A_POINT},
};

static int no_point = 1;


void e_loop(SDL_Renderer *rend, TTF_Font *font){
	ix = iy = 0;

	// set movement
	switch(dir){
		case D_UP: iy = -STEP; break;
		case D_DOWN: iy = STEP; break;
		case D_RIGHT: ix = STEP; break;
		case D_LEFT: ix = -STEP; break;
		default: break;
	}



	int idx;

	static struct BLOCK new_blocks[MAXBLOCKS];
	// continuous movement
	copy_blocks(new_blocks, blocks);
	new_blocks[0].x = blocks[0].x + ix;  // head x
	new_blocks[0].y = blocks[0].y + iy;  // head y
	for(idx = 1; blocks[idx].x; ++idx){
		if(new_blocks[idx].act == A_BODY){
			new_blocks[idx].x = blocks[idx - 1].x;
			new_blocks[idx].y = blocks[idx - 1].y;
		}
	}


	// if(new_blocks[0].y == 0){
	// 	printf("HIT\n");
	// }

	// printf("[%i, %i]\n", new_blocks[0].x, new_blocks[0].y);

	if(new_blocks[idx - 1].x == new_blocks[0].x && new_blocks[idx - 1].y == new_blocks[0].y){
		points++;

		switch((int)(points / 10) + 1){
			case 1: lvl = 1; game_speed = 200; break;
			case 2: lvl = 2; game_speed = 150; break;
			case 3: lvl = 3; game_speed = 100; break;
			case 4: lvl = 4; game_speed = 50; break;
			default: break;
		}

		struct BLOCK newb = {new_blocks[idx - 2].x, new_blocks[idx - 2].y, A_BODY};
		new_blocks[idx - 1] = newb;

		int _max[3] = {X_SCALE - 1, Y_SCALE - 1,  STEP};
		new_blocks[idx] = unique_block(new_blocks, _max, A_POINT);
	}

	if(no_point && blocks[idx - 1].act != A_POINT){
		int _max[3] = {X_SCALE - 1, Y_SCALE - 1,  STEP};
		new_blocks[idx] = unique_block(new_blocks, _max, A_POINT);
		no_point = 0;
	}

	copy_blocks(blocks, new_blocks);  // save state

	if(bock_corssed(new_blocks[0], blocks) != -1)
		gof(rend, font, points, "You can't cross yourself");


	char header[100];
	sprintf(header, "Points: %i    Level: %i", points, lvl);

	draw_frame(rend, font, new_blocks, on_hit, header);

	if(gofa)
		gof(rend, font, points, "You can't cross frame");

}

void restart(){
	lvl = 1;
	dir = D_UP;
	gofa = 0;
	running = 1;
	no_point = 1;
	points = 0;

	struct BLOCK b[MAXBLOCKS] = {
		{STEP * 10, STEP * 7, A_HEAD},
		{STEP * 10, STEP * 8, A_BODY},
		{STEP * 10, STEP * 9, A_BODY},
	};
	copy_blocks(blocks, b);
}

int main(void){
	width = (STEP * X_SCALE) + STEP;
	height = (STEP * Y_SCALE) + STEP;
	restart();
	loop_event(width, height, e_loop);
	return 0;
}

