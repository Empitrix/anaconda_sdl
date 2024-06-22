#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "src/rules.h"
#include "src/screen.h"
#include "src/loop.h"


// macros
#define STEP 30
#define MAXBLOCKS 10000


static int ix, iy = 0;
volatile int points = 0;


void continuous(enum DIRECTION dir){
	int *out = malloc(2);
	ix = iy = 0;
	if(dir == D_UP)
		--iy;
	else if(dir == D_DOWN)
		++iy;
	else if(dir == D_RIGHT)
		++ix;
	else
		--ix;
}


void on_hit(void){ running = 0; }
void on_get(void){ points = points + 1; }


void gof(int score, char *format, ...){
	char message[1000];
	va_list aptr;
	int ret;
	va_start(aptr, format);
	ret = vsprintf(message, format, aptr);
	va_end(aptr);
	printf("Point%s: %i\n", points <= 1 ? "" : "s", points);
	printf("%s\n", message);
	running = 0;
}

static int width, height;


static int lvl = 1;
static struct BLOCK blocks[MAXBLOCKS] = {
	{STEP * 10, STEP * 7, A_HEAD, HEAD_BLOCK},
	{20, 20, A_POINT, CHEE_BLOCK},
};



void e_loop(SDL_Renderer *rend){
	ix = iy = 0;

	// // check for size
	switch(dir){
		case D_UP: iy = -STEP;   printf("UP\n"); break;
		case D_DOWN: iy = STEP;  printf("DOWN\n"); break;
		case D_RIGHT: ix = STEP; printf("RIGHT\n"); break;
		case D_LEFT: ix = -STEP; printf("LEFT\n"); break;
		default:
			break;
	}



	/*
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

	if(new_blocks[idx - 1].x == new_blocks[0].x && new_blocks[idx - 1].y == new_blocks[0].y){
		points++;

		// switch((int)(points / 10) + 1){
		// 	case 1: lvl = 1; game_speed = 200; break;
		// 	case 2: lvl = 2; game_speed = 150; break;
		// 	case 3: lvl = 3; game_speed = 100; break;
		// 	case 4: lvl = 4; game_speed = 50; break;
		// 	default: break;
		// }

		struct BLOCK newb = {new_blocks[idx - 2].x, new_blocks[idx - 2].y, A_BODY, BODY_BLOCK};
		new_blocks[idx - 1] = newb;

		// int _max[2] = {width, height};
		// new_blocks[idx] = unique_block(new_blocks, _max, CHEE_BLOCK, A_POINT);
	}

	copy_blocks(blocks, new_blocks);  // save state

	// if(bock_corssed(new_blocks[0], blocks) != -1)
	// 	gof(points, "You can't cross yourself");


	char header[100];
	sprintf(header, "Points: %i, Lvl: %i", points, lvl);

	draw_frame(rend, new_blocks, on_hit, on_get, header);
	*/

	if(running == 0)
		gof(points, "You can't cross frame");

	// predir = dir;
}


int main(void){
	lvl = 1;
	width = STEP * 20;
	height = STEP * 15;
	loop_event(width, height, e_loop);
	return 0;
}

