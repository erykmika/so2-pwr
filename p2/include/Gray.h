#ifndef GRAY
#define GRAY

#include "env.h"
#include "Data.h"
#include <utility>

/* Class resposnible for the gray area thread */
class Gray
{
public:
    static void run(Data *data);
    static bool isBallTouching(Data *data, uint8_t id);
};

#endif
