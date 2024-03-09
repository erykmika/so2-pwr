#ifndef BALL
#define BALL

#include <random>

#define BALL_HEALTH 5  // Number of bounces before disappearing
#define DELAY_TIME 250 // ms

class Ball
{
public:
    Ball();
    int getHealth() const;

private:
    /* Number of remaining bounces */
    unsigned short health;
    /* Number of phases (that are DELAY_TIME long) needed to make a move */
    unsigned short delayLimit;
    /* Current number of delay phases passed */
    unsigned short delayCounter;
};

#endif