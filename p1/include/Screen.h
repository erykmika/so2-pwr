#ifndef SCRIN
#define SCRIN

#include <ncurses.h>
#include "env.h"
#include "Coords.h"

class Screen
{
public:
    static void initThread(Coords &coords);

private:
    void run();
    Screen(Coords &coords);
    void initScreen();
    void updateScreen();
    Coords curCoords;
    Coords oldCoords;
    WINDOW *window;
};

#endif
