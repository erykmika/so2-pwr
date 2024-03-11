#ifndef BALL
#define BALL

#include "env.h"
#include "Data.h"

/* Class representing Ball objects that are single threads of execution */
class Ball
{
public:
    static void run(uint8_t id, Data *data);
};

#endif
