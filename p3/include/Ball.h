#ifndef BALL
#define BALL

#include "env.h"
#include "Data.h"
#include "Gray.h"

/* Class representing Ball objects that are single threads of execution */
class Ball
{
public:
    static void run(uint8_t id, Data *data);
    static bool checkGrayHorizontalCollision(uint8_t id, Data *data);
    static bool checkGrayVerticalCollision(uint8_t id, Data *data, short xDirection);
    static void checkIfInsideGray(uint8_t id, Data *Data);
};

#endif
