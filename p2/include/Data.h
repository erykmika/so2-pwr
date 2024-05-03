#ifndef COORDS
#define COORDS
#include "env.h"
#include <vector>
#include <mutex>
#include <condition_variable>

/**
 * Struct holding information about (x, y) positions of balls
 * It also contains (x, y) values of the bottom leftmost point of the gray area
 * And the exit key flag
 */
struct Data
{
    /** Ball coordinates */
    std::vector<uint8_t> ballsX{NUM_OF_BALLS};
    std::vector<uint8_t> ballsY{NUM_OF_BALLS};
    /** Is ball alive */
    std::vector<bool> ballsAlive;
    /** Gray area left bottom point */
    uint8_t grayX = 0;
    uint8_t grayY = 0;
    /** Is gray area active */
    bool grayAlive;
    /** Exit key flag */
    int exit_flag;
    /** Gray x mutex */
    std::vector<std::mutex> x_mutex;
    /** Condition variable for signaling ball-gray area collisions */
    std::condition_variable cv_ball_gray_collision;
    /** Mutex for protecting shared data */
    std::mutex data_mutex;
    /** If the gray area has moved */
    bool gray_moved;
};

#endif
