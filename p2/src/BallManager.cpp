#include "BallManager.h"

void BallManager::run(Data *data)
{
    std::vector<std::thread> ballThreads;

    for (auto i = 0; i < NUM_OF_BALLS; i++)
    {
        std::thread bt(Ball::run, i, data);
        ballThreads.push_back(move(bt));
    }
    for (auto i = 0; i < NUM_OF_BALLS; i++)
    {
        ballThreads[i].join();
    }
}
