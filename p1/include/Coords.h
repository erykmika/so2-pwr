#ifndef COORDS
#define COORDS
#include "env.h"

/**
 * Struct holding information about (x, y) positions of balls
 * It also contains (x, y) values of the bottom leftmost point of the gray area
 */
struct Coords
{
    /** Ball coordinates */
    std::vector<uint8_t> ballsX{NUM_OF_BALLS};
    std::vector<uint8_t> ballsY{NUM_OF_BALLS};
    /** Gray area left bottom point */
    uint8_t grayX = 0;
    uint8_t grayY = 0;
};

#endif
