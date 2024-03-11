#include "env.h"
#include "Screen.h"
#include "BallManager.h"

int main()
{
    /* Data struct initialization */
    Data *data = new Data;
    for (auto i = 0; i < NUM_OF_BALLS; i++)
    {
        data->ballsX[i] = 0;
        data->ballsY[i] = 0;
        data->ballsAlive.push_back(false);
    }
    data->exit_flag = ERR;

    // Spawn threads
    std::thread ballManagerThr(BallManager::initThread, data);
    std::thread screenThr(Screen::run, data);

    // Wait for threads to complete
    screenThr.join();
    ballManagerThr.join();

    // Free resources
    delete data;
}
