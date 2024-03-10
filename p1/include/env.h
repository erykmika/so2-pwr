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
#define WINDOW_WIDTH 80
#define WINDOW_HEIGHT 35

/* Ball properties */
#define NUM_OF_BALLS 50 // Maximum number of balls on the screen
#define BALL_HEALTH 5   // Number of bounces before disappearing
#define TICK 250        // ms
/* Time delay of individual balls */
#define BALL_MIN_DELAY 1 // s
#define BALL_MAX_DELAY 5 // s
#define MOD_DELAY BALL_MAX_DELAY + 1 - BALL_MIN_DELAY

#endif
