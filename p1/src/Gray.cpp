#include "Gray.h"

void Gray::run(Data *data)
{
    while (data->exit_flag != EXIT_KEY)
    {
        uint8_t &x = data->grayX;
        uint8_t &y = data->grayY;

        x = rand()%(WINDOW_WIDTH - GRAY_WIDTH) + 5;
        y = WINDOW_HEIGHT - 3;

        // Gray area speed
        uint8_t speed = INITIAL_GRAY_SPEED;

        data->grayAlive = true;

        uint8_t yDirection = -1;

        while (data->exit_flag != EXIT_KEY)
        {
            // Bounce off horizontal edges, change speed to random value
            if (y == WINDOW_HEIGHT - 2 || y - GRAY_HEIGHT == 0)
            {
                yDirection = -yDirection;
                speed = rand() % MOD_GRAY_SPEED + MAX_GRAY_SPEED;
            }

            y += yDirection;

            for (uint8_t i = 0; i < speed; i++)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(TICK));
            }
        }
    }
    data->grayAlive = false;
}
