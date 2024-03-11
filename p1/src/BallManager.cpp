#include "BallManager.h"

void BallManager::initThread(Coords *coords)
{
    std::thread ballThreads[NUM_OF_BALLS];
    for (auto i = 0; i < NUM_OF_BALLS; i++)
    {
        ballThreads[i] = std::thread(Ball::run, i, coords);
    }

    for (auto i = 0; i < NUM_OF_BALLS; i++)
    {
        ballThreads[i].join();
    }
}
