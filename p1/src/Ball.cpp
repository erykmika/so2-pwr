#include "Ball.h"

/* Wait and then start the ball thread logic */
void Ball::run(uint8_t id, Data *data)
{
    while (data->exit_flag != EXIT_KEY)
    {
        sleep(rand() % (MOD_DELAY) + BALL_MIN_DELAY);

        uint8_t health = BALL_HEALTH;
        uint8_t delayLimit = rand() % (MOD_SPEED) + MAX_SPEED;

        uint8_t &x = data->ballsX[id];
        uint8_t &y = data->ballsY[id];

        uint8_t yDirection = -1;
        uint8_t xDirection = (rand() % 3) - 1; // <-1, 1>

        // Ball enters the board
        x = (rand() % SPAWN_X_LEN) + LOW_X_SPAWN;
        y = SPAWN_Y;

        // From now on the ball can be drawn on screen
        data->ballsAlive[id] = true;

        for (auto i = 0; i < delayLimit; i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(TICK));
        }

        x += xDirection;
        y += yDirection;

        while (health && data->exit_flag != EXIT_KEY)
        {
            for (auto i = 0; i < delayLimit; i++)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(TICK));
            }

            /* Collision detection */
            bool horizontal_collision = (y == 1 || y == WINDOW_HEIGHT - 2);
            bool vertical_collision = (x == 1 || x == WINDOW_WIDTH - 2);

            // corner collision
            if (horizontal_collision && vertical_collision)
            {
                xDirection = -xDirection;
                yDirection = -yDirection;
            }

            // upper & bottom edge
            else if (horizontal_collision)
            {
                yDirection = -yDirection;
                if (!xDirection)
                {
                    xDirection = rand() % 3 - 1;
                }
                --health;
            }
            // left & right edge
            else if (vertical_collision)
            {
                xDirection = -xDirection;
                if (!yDirection)
                {
                    yDirection = rand() % 3 - 1;
                }
                --health;
            }
            x += xDirection;
            y += yDirection;
        }
        // Ball disappears
        data->ballsAlive[id] = false;
    }
}
