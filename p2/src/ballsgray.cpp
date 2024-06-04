#include "Gray.h"
#include "Ball.h"

void Gray::run(Data *data)
{
    while (data->exit_flag != EXIT_KEY)
    {
        uint8_t &x = data->grayX;
        uint8_t &y = data->grayY;

        x = 25;
        y = WINDOW_HEIGHT - 10;

        // Gray area speed
        short speed = INITIAL_GRAY_SPEED;

        data->grayAlive = true;

        short yDirection = -1;

        while (data->exit_flag != EXIT_KEY)
        {
            {
                std::lock_guard lk(data->grayMutex);

                if (data->is_touching)
                {
                    continue;
                }

                // Bounce off horizontal edges, change speed to random value
                if (y == WINDOW_HEIGHT - 2 || y - GRAY_HEIGHT == 0)
                {
                    yDirection = -yDirection;
                    speed = rand() % MOD_GRAY_SPEED + MAX_GRAY_SPEED;
                }
                y += yDirection; // Move the gray area
            }
            for (uint8_t i = 0; i < speed; i++)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(TICK));
            }
        }
    }
    data->grayAlive = false;
}

/* Wait and then start the ball thread logic */
void Ball::run(uint8_t id, Data *data)
{
    uint8_t &x = data->ballsX[id];
    uint8_t &y = data->ballsY[id];

    uint8_t &grayX = data->grayX;
    uint8_t &grayY = data->grayY;

    while (data->exit_flag != EXIT_KEY)
    {
        sleep(rand() % (MOD_DELAY) + BALL_MIN_DELAY);

        short health = BALL_HEALTH;
        uint8_t delayLimit = rand() % (MOD_SPEED) + MAX_SPEED;

        short yDirection = -1;
        short xDirection = rand() % 3 - 1; // <-1, 1>

        // Ball enters the board
        x = (rand() % SPAWN_X_LEN) + LOW_X_SPAWN;
        y = SPAWN_Y;

        // From now on the ball can be drawn on screen
        data->ballsAlive[id] = true;

        for (auto i = 0; i < delayLimit; i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(GRAY_TOUCH_HOLD));
        }

        // Proper order must be kept, the gray area first, then the ball
        x += xDirection;
        y += yDirection;

        while (health && data->exit_flag != EXIT_KEY)
        {

            // Check if the ball collides with the gray area - gray surroundings are checked only
            if (((x >= grayX - 1 && x <= grayX + 1) ||
                 (x >= grayX + GRAY_WIDTH - 2 && x <= grayX + GRAY_WIDTH)) &&
                (y <= grayY + 2 && y >= grayY - GRAY_HEIGHT - 1))
            {
                {
                    std::unique_lock lk(data->grayMutex);

                    bool gray_horizontal_collision = checkGrayHorizontalCollision(id, data);
                    bool gray_vertical_collision = checkGrayVerticalCollision(id, data, xDirection);

                    if (gray_vertical_collision)
                    {
                        xDirection = -xDirection;
                        if (!yDirection)
                        {
                            yDirection = rand() % 3 - 1;
                        }
                        // Drop health only if the ball is outside of the gray area
                        if (x <= grayX - 1 || x >= grayX + GRAY_WIDTH)
                        {
                            --health;
                        }
                    }

                    else if (gray_horizontal_collision)
                    {
                        yDirection = -yDirection;
                        if (!xDirection)
                        {
                            xDirection = rand() % 3 - 1;
                        }
                        --health;
                    }

                    x = std::min(std::max(1, x + xDirection), WINDOW_WIDTH - 2);

                    if ((x == grayX || x == grayX + GRAY_WIDTH - 1) && (y <= grayY + 2 && y >= grayY - GRAY_HEIGHT - 1))
                    {
                        data->is_touching |= ((uint16_t)0x1 << id);
                        if ((WINDOW_HEIGHT)-y <= 4 || y <= 3)
                        {
                            x += 3;
                        }
                    }
                    else
                    {
                        data->is_touching &= ~((uint16_t)0x1 << id);
                    }

                    if (gray_horizontal_collision)
                    {
                        y = std::min(std::max(1, y + 3 * yDirection), WINDOW_HEIGHT - 2);
                    }
                    else
                    {
                        y = std::min(std::max(1, y + yDirection), WINDOW_HEIGHT - 2);
                    }
                }
            }
            else
            {
                data->is_touching &= ~((uint16_t)0x1 << id);

                bool horizontal_collision = (y == 1 || y == WINDOW_HEIGHT - 2);
                bool vertical_collision = (x == 1 || x == WINDOW_WIDTH - 2);

                // corner collision
                if ((horizontal_collision && vertical_collision))
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

                else if (vertical_collision || horizontal_collision)
                {
                    yDirection = yDirection ? (yDirection / abs(yDirection)) : yDirection;
                }
                x = std::min(std::max(1, x + xDirection), WINDOW_WIDTH - 2);
                y = std::min(std::max(1, y + yDirection), WINDOW_HEIGHT - 2);
            }
            // Ball movement delay
            for (auto i = 0; i < delayLimit; i++)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(TICK));
            }
        }
        data->is_touching &= ~((uint16_t)0x1 << id);
        data->ballsAlive[id] = false;
    }
}

bool Ball::checkGrayHorizontalCollision(uint8_t id, Data *data)
{
    short grayX = data->grayX;
    short grayY = data->grayY;
    short x = data->ballsX[id];
    short y = data->ballsY[id];
    return ((x == grayX || x == grayX + GRAY_WIDTH - 1) &&
            (y == grayY + 1 || y == grayY - GRAY_HEIGHT));
}

bool Ball::checkGrayVerticalCollision(uint8_t id, Data *data, short xDirection)
{
    short grayX = data->grayX;
    short grayY = data->grayY;
    short x = data->ballsX[id];
    short y = data->ballsY[id];
    return ((y <= grayY + 1 && y >= grayY - GRAY_HEIGHT) &&
            ((x == grayX - 1 && xDirection > 0) || (x == grayX + 1 && xDirection < 0) || (x == grayX + GRAY_WIDTH && xDirection < 0) || (x == grayX + GRAY_WIDTH - 2 && xDirection > 0)));
}
