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

/** Own header files */
/* ncurses screen properties */
#define WINDOW_WIDTH 100
#define WINDOW_HEIGHT 50
#define REFRESH_RATE 100 // ms

/* Ball properties */
#define NUM_OF_BALLS 20             // Maximum number of balls on the screen
#define BALL_HEALTH 5               // Number of bounces before disappearing
#define TICK 100                    // ms
#define SPAWN_Y (WINDOW_HEIGHT - 3) // y value of balls spawn point
#define MIN_SPEED 3                 // Min ball ticks (ticks/move)
#define MAX_SPEED 1                 // Max ball ticks (ticks/move)
#define MOD_SPEED MIN_SPEED + 1 - MAX_SPEED

/* Start delay of individual balls */
#define BALL_MIN_DELAY 1 // s
#define BALL_MAX_DELAY 8 // s
#define MOD_DELAY BALL_MAX_DELAY + 1 - BALL_MIN_DELAY

#endif
