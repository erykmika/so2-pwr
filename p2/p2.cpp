/* Eryk Mika 264451 */

#include "env.h"
#include "Screen.h"
#include "BallManager.h"
#include "Gray.h"
#include <mutex>

int main()
{
    // Initialize random number generator
    srand(time(NULL));

    /* Data struct initialization */
    Data *data = new Data;
    for (auto i = 0; i < NUM_OF_BALLS; i++)
    {
        data->ballsX[i] = 0;
        data->ballsY[i] = 0;
        data->ballsAlive.push_back(false);
    }

    data->exit_flag = ERR;
    data->grayX = 0;
    data->grayY = 0;
    data->grayAlive = false;
    data->gray_moved = false;

    // Spawn threads
    std::thread ballManagerThr(BallManager::run, data);
    std::thread grayThr(Gray::run, data);
    std::thread screenThr(Screen::run, data);

    // Wait for threads to complete
    screenThr.join();
    grayThr.join();
    ballManagerThr.join();

    // Free resources
    delete data;
}
