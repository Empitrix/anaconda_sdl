#include <SDL2/SDL_events.h>
#include <SDL2/SDL_scancode.h>
#include <stdio.h>
#include "rules.h"
#include "structs.h"

void getdir(SDL_Event event){
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				running = 0;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode) {
					case SDL_SCANCODE_Q:
						running = 0;
						break;

					case SDL_SCANCODE_UP:
						if(dir != D_DOWN)
							dir = D_UP;
						break;
					case SDL_SCANCODE_DOWN:
						if(dir != D_UP)
							dir = D_DOWN;
						break;
					case SDL_SCANCODE_LEFT:
						if(dir != D_RIGHT)
							dir = D_LEFT;
						break;
					case SDL_SCANCODE_RIGHT:
						if(dir != D_LEFT)
							dir = D_RIGHT;
						break;
					default:
						break;
				}
		}
	}
}

