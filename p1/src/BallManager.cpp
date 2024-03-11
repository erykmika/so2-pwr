#include "BallManager.h"

void BallManager::initThread(Data *data)
{
    std::thread ballThreads[NUM_OF_BALLS];
    //  while (data->exit_flag != EXIT_KEY)
    //  {
    for (auto i = 0; i < NUM_OF_BALLS; i++)
    {
        if (!data->ballsAlive[i])
            ballThreads[i] = std::thread(Ball::run, i, data);
    }
    //     sleep(1);
    //}
    for (auto i = 0; i < NUM_OF_BALLS; i++)
    {
        ballThreads[i].join();
    }
}
