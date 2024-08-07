#include <time.h>
#include <stdlib.h>
#include "structs.h"
 
// wait by milliseconds
void delay_ms(int ms){
	clock_t start_time = clock();
	while (clock() < start_time + (1000 * ms));
}


int contain_coord(int x, int y, struct BLOCK blocks[]){
	int i;
	for(i = 0; blocks[i].x; ++i){
		if(blocks[i].x - 1 == x && blocks[i].y == y){
			return i;
		}
	}
	return -1;
}


// copy array of blocks pr to se
void copy_blocks(struct BLOCK se[], struct BLOCK pa[]){
	int idx;
	for(idx = 0; pa[idx].x; ++idx){
		se[idx] = pa[idx];
	}
}


int randint(int min, int max){
	return rand() % max + min;
}


int bock_corssed(struct BLOCK block, struct BLOCK blocks[]){
	int i;
	for(i = 0; blocks[i].x; ++i){
		if(blocks[i].x == block.x && blocks[i].y == block.y && blocks[i].act == A_BODY){
			return i;
		}
	}
	return -1;
}


struct BLOCK unique_block(struct BLOCK blocks[], int max[3], enum BLOCK_ACT act){
	struct BLOCK block;

	do{
		int tx = randint(1, max[0]);
		int ty = randint(3, max[1]);
		block = (struct BLOCK){tx, ty, act};

	} while(bock_corssed(block, blocks) != -1);

	block.x = block.x * max[2];
	block.y = block.y * max[2];
	return block;
}

