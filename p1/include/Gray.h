#ifndef GRAY
#define GRAY

#include "env.h"
#include "Data.h"

/* Class resposnible for the gray area thread */
class Gray
{
public:
    static void run(Data *data);
};

#endif
