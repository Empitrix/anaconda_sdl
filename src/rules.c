#include "structs.h"

#define STEP 15

#define SDL_WKLR (SDL_Color){255, 255, 255, 255}

#define X_SCALE 50
#define Y_SCALE 45


#define TOPSIZ 30 - 1

#define FONTSIZ 18


/* Colors */

// border
#define BKLR (SDL_Color){30, 30, 30, 255}
// backgournd color
#define BGKLR (SDL_Color){30, 30, 30, 255}

// game head
#define GHKLR (SDL_Color){240, 30, 44, 255}
// game body
#define GBKLR (SDL_Color){30, 123, 97, 255}
// game point
#define GPKLR (SDL_Color){29, 158, 224, 255}

volatile int game_speed = 200;
int running = 1;

static int gofa = 0;
enum DIRECTION dir = D_UP;


