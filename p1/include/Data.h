#ifndef COORDS
#define COORDS
#include "env.h"

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
};

#endif
