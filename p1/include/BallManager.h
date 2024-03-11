#ifndef BALL_MANAGER
#define BALL_MANAGER

#include "env.h"
#include "Ball.h"

/* Thread class managing the Ball thread instances*/
class BallManager
{
public:
    static void initThread(Data *data);
};

#endif
