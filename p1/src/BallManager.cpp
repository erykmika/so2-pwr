#include "BallManager.h"

void BallManager::run(Data *data)
{
    std::thread ballThreads[NUM_OF_BALLS];

    for (auto i = 0; i < NUM_OF_BALLS; i++)
    {
        ballThreads[i] = std::thread(Ball::run, i, data);
    }
    for (auto i = 0; i < NUM_OF_BALLS; i++)
    {
        ballThreads[i].join();
    }
}
