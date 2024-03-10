#include "Ball.h"

Ball::Ball(uint8_t id, Coords &coords)
{
    this->id = id;
    this->coords = coords;
    this->health = BALL_HEALTH;
    this->delayLimit = rand() % 4 + 2;
    this->delayCounter = 0;
}

/* Wait and then start the ball thread logic */
void Ball::run()
{
    srand(time(NULL));
    sleep(rand() % (MOD_DELAY) + BALL_MIN_DELAY);
}
