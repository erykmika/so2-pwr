#ifndef BALL
#define BALL

#include "env.h"
#include "Coords.h"

/* Class representing a Ball objects that is a single thread of execution */
class Ball
{
public:
    Ball(uint8_t id, Coords &coords);
    void run();

private:
    void move();
    /* Ball id */
    uint8_t id;
    /* Number of remaining bounces */
    uint8_t health;
    /* Number of TICKs needed to make a move */
    uint8_t delayLimit;
    /* Current number of delay phases passed */
    uint8_t delayCounter;
    /* Reference to Coords struct */
    Coords coords;
};

#endif
