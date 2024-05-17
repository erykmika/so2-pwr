#ifndef ENV
#define ENV

/* Included libraries */
#include <random>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <random>
#include <time.h>
#include <vector>
#include <utility>
#include <cstdint>
#include <chrono>

/* ncurses screen properties */
#define WINDOW_WIDTH 60
#define WINDOW_HEIGHT 30

#define TICK 200 // ms

/* Ball properties */
#define NUM_OF_BALLS 10 // Maximum number of balls on the screen
#define BALL_HEALTH 20  // Number of bounces before disappearing
#define SPAWN_X_LEN 20
#define LOW_X_SPAWN (WINDOW_WIDTH / 2) - (SPAWN_X_LEN / 2)
#define SPAWN_Y (WINDOW_HEIGHT - 2) // y value of balls spawn point
#define MIN_SPEED 1                 // Min ball ticks (ticks/move)
#define MAX_SPEED 1                 // Max ball ticks (ticks/move)
#define MOD_SPEED MIN_SPEED + 1 - MAX_SPEED

/* Start delay of individual balls */
#define BALL_MIN_DELAY 1 // s
#define BALL_MAX_DELAY 5 // s
#define MOD_DELAY BALL_MAX_DELAY + 1 - BALL_MIN_DELAY

/* Gray area properties */
#define GRAY_WIDTH 10
#define GRAY_HEIGHT 10
#define INITIAL_GRAY_SPEED 1 // Gray area speed (ticks per move)
#define MIN_GRAY_SPEED 1     // Min gray area ticks (ticks/move)
#define MAX_GRAY_SPEED 1     // Max gray area ticks (ticks/move)
#define MOD_GRAY_SPEED MIN_GRAY_SPEED + 1 - MAX_GRAY_SPEED

/** Exit key */
#define EXIT_KEY ' '

#endif
