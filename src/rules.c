#include "structs.h"

#define HEAD_BLOCK "\x1B[31m■\x1B[0m"  // HEAD BLOCK
#define BODY_BLOCK "\x1B[32m■\x1B[0m"  // BODY BLOCK
#define CHEE_BLOCK "\x1B[33m\x1B[0m"  // POINT BLOCK

// extern volatile int game_speed = 100;
volatile int game_speed = 200;
int running = 1;

// enum DIRECTION predir = D_UP;
enum DIRECTION dir = D_UP;

