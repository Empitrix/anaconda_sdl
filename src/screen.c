#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void cls(void){
	system("clear");
}


void draw_frame(int w, int h, struct BLOCK blocks[]){
	int x, y;
	x = y = 0;
	cls();

	while(y < (h + 1)){
		while(x < (w + 1)){

			if(x == w || x == 0)
				if(y == 0 && x == 0 )
					printf("┌");
				else if(y == 0 && x == w )
					printf("┐");
				else if(y == h && x == 0 )
					printf("└");
				else if(y == h && x == w )
					printf("┘");
				else if(y == 2 && x == 0 )
					printf("├");
				else if(y == 2 && x == w )
					printf("┤");
				else
					printf("│");
			else
				if(y == 1)
					printf(" ");
				else
					if(y == 2 || y == 0 || y == h)
						printf("─");
					else{
						int contain = contain_coord(x, y - 2, blocks);
						if(contain){
							// printf("*");
							// printf("");
							printf("󰮯");
						} else{
							printf(" ");
						}
					}
			++x;
		}
		putchar('\n');
		++y;
		x = 0;
	}
}

