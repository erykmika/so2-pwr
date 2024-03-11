#include "env.h"
#include "Screen.h"
#include "BallManager.h"

int main()
{
    Coords *coords = new Coords;
    for (auto i = 0; i < NUM_OF_BALLS; i++)
    {
        coords->ballsX[i] = 0;
        coords->ballsY[i] = 0;
    }
    std::thread ballManagerThr(BallManager::initThread, coords);
    std::thread screenThr(Screen::initThread, coords);

    ballManagerThr.join();
    screenThr.join();

    delete coords;
}
