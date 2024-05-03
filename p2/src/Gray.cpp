#include "Gray.h"

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
            // Bounce off horizontal edges, change speed to random value
            if (y == WINDOW_HEIGHT - 2 || y - GRAY_HEIGHT == 0)
            {
                yDirection = -yDirection;
                speed = rand() % MOD_GRAY_SPEED + MAX_GRAY_SPEED;
            }

            // Acquire locks for all mutexes in the vector
            for (auto &mutex : data->x_mutex)
            {
                std::lock_guard<std::mutex> lg(mutex);
            }

            y += yDirection; // Move the gray area

            data->gray_moved = true;

            // Notify waiting threads (balls) after gray area position update
            data->cv_ball_gray_collision.notify_all();

            // No need to release locks explicitly, they are released when going out of scope

            for (uint8_t i = 0; i < speed; i++)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(TICK));
            }

            data->gray_moved = false;
        }
    }
    data->grayAlive = false;
}
