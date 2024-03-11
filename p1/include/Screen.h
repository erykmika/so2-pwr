#ifndef SCRIN
#define SCRIN

#include <ncurses.h>
#include "env.h"
#include "Data.h"

// Class responsible for the ncurses screen thread
class Screen
{
public:
    static void run(Data *data);

private:
    Screen(Data *data);
    void initScreen();
    void updateScreen();
    Data *curData;
    std::vector<uint8_t> oldX;
    std::vector<uint8_t> oldY;
    WINDOW *window;
};

#endif
