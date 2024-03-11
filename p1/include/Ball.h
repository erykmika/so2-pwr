#ifndef BALL
#define BALL

#include "env.h"
#include "Coords.h"

/* Class representing Ball objects that are single threads of execution */
class Ball
{
public:
    static void run(uint8_t id, Coords *coords);
};

#endif
