#include "Ball.h"

Ball::Ball()
{
    health = BALL_HEALTH;
    delayLimit = rand() % 4 + 2;
    delayCounter = 0;
}

int Ball::getHealth() const
{
    return health;
}
