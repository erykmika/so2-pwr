#include "Gray.h"
#include "Ball.h"

bool gray_moved = false;

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

        // Mutexes specific to particular balls
        // Balls wait for the gray area to move unless any ball touches the gray area - then wait
        bool touching_detected = false;

        while (data->exit_flag != EXIT_KEY)
        {
            while (touching_detected)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(TICK));
                touching_detected = false;
            }

            {
                std::lock_guard lk(data->grayMutex);

                if (data->is_touching)
                {
                    touching_detected = true;
                }

                if (!touching_detected)
                {
                    // Bounce off horizontal edges, change speed to random value
                    if (y == WINDOW_HEIGHT - 2 || y - GRAY_HEIGHT == 0)
                    {
                        yDirection = -yDirection;
                        speed = rand() % MOD_GRAY_SPEED + MAX_GRAY_SPEED;
                    }
                    y += yDirection; // Move the gray area
                }

                gray_moved = true;
                data->cv.notify_all();

                if (touching_detected)
                {
                    continue;
                }
            }
            for (uint8_t i = 0; i < speed; i++)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(TICK));
            }

            gray_moved = false;
        }
    }
    data->grayAlive = false;
}

/* Wait and then start the ball thread logic */
void Ball::run(uint8_t id, Data *data)
{
    while (data->exit_flag != EXIT_KEY)
    {
        sleep(rand() % (MOD_DELAY) + BALL_MIN_DELAY);

        short health = BALL_HEALTH;
        uint8_t delayLimit = rand() % (MOD_SPEED) + MAX_SPEED;

        uint8_t &x = data->ballsX[id];
        uint8_t &y = data->ballsY[id];

        short yDirection = -1;
        short xDirection = 0; // <-1, 1>

        // Ball enters the board
        x = 25;
        y = SPAWN_Y;

        // From now on the ball can be drawn on screen
        data->ballsAlive[id] = true;

        for (auto i = 0; i < delayLimit; i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(TICK));
        }

        // Proper order must be kept, the gray area first, then the ball
        x += xDirection;
        y += yDirection;

        while (health && data->exit_flag != EXIT_KEY)
        {
            for (auto i = 0; i < delayLimit; i++)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(TICK));
            }

            uint8_t &grayX = data->grayX;
            uint8_t &grayY = data->grayY;

            // Check if the ball collides with the gray area - gray surroundings are checked only
            if (((x >= grayX - 2 && x <= grayX + 2) ||
                 (x >= grayX + GRAY_WIDTH - 3 && x <= grayX + GRAY_WIDTH + 2)) &&
                (y <= grayY + 2 && y >= grayY - GRAY_HEIGHT - 1))
            {
                {
                    std::unique_lock lk(data->grayMutex);
                    data->cv.wait(lk, []
                                  { return gray_moved; });

                    bool gray_horizontal_collision = checkGrayHorizontalCollision(id, data);
                    bool gray_vertical_collision = checkGrayVerticalCollision(id, data, xDirection);

                    if (gray_vertical_collision)
                    {
                        xDirection = -xDirection;
                        if (!yDirection)
                        {
                            yDirection = rand() % 3 - 1;
                        }
                        --health;
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

                    if (gray_horizontal_collision)
                    {
                        data->is_touching |= ((uint16_t)0x1 << id);
                        y = std::min(std::max(1, y + 3 * yDirection), WINDOW_HEIGHT - 2);
                    }
                    else if (gray_vertical_collision)
                    {
                        data->is_touching &= ~((uint16_t)0x1 << id); // 0100 => FEFF
                        y = std::min(std::max(1, y + yDirection), WINDOW_HEIGHT - 2);
                    }
                    else
                    {
                        data->is_touching &= ~((uint16_t)0x1 << id); // 0100 => FEFF
                        y = std::min(std::max(1, y + yDirection), WINDOW_HEIGHT - 2);
                    }

                    data->cv.notify_all();
                }
            }
            else
            {
                data->is_touching &= ~((uint16_t)0x1 << id); // 0100 => FEFF

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
        }
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
