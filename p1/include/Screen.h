#ifndef SCRIN
#define SCRIN

#include <ncurses.h>
#include "env.h"
#include "Coords.h"

// Class responsible for the ncurses screen thread
class Screen
{
public:
    static void initThread(Coords *coords);

private:
    Screen(Coords *coords);
    void initScreen();
    void updateScreen();
    Coords *curCoords;
    std::vector<uint8_t> oldX;
    std::vector<uint8_t> oldY;
    WINDOW *window;
};

#endif
