#include "Ball.h"

/* Wait and then start the ball thread logic */
void Ball::run(uint8_t id, Coords *coords)
{
    // uint8_t health = BALL_HEALTH;
    sleep(rand() % (MOD_DELAY) + BALL_MIN_DELAY);

    uint8_t delayLimit = rand() % (MOD_SPEED) + MAX_SPEED;

    uint8_t &x = coords->ballsX[id];
    uint8_t &y = coords->ballsY[id];

    x = rand() % (WINDOW_WIDTH - 39) + 20;
    y = SPAWN_Y;
    uint8_t yDirection = -1;
    uint8_t xDirection = (rand() % 3) - 1; // <-1, 1>
    while (1)
    {
        for (auto i = 0; i < delayLimit; i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(TICK));
        }

        /* Collision detection */

        // upper & bottom edge
        if (y == 1 || y == WINDOW_HEIGHT - 2)
        {
            yDirection = -yDirection;
            if (xDirection == 0)
            {
                xDirection = rand() % 3 - 1;
            }
        }
        // left & right edge
        if (x == 1 || x == WINDOW_WIDTH - 2)
        {
            xDirection = -xDirection;
            if (yDirection == 0)
            {
                yDirection = rand() % 3 - 1;
            }
        }

        x += xDirection;
        y += yDirection;
    }
}
