#include "Screen.h"

Screen::Screen(Coords *coords)
{
    curCoords = coords;
    window = nullptr;
}

void Screen::initThread(Coords *coords)
{
    Screen scr(coords);
    scr.initScreen();
    while (true)
    {
        scr.updateScreen();
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(REFRESH_RATE));
    }
    getch();
    endwin();
}

void Screen::initScreen()
{
    window = initscr();
    noecho();
    curs_set(0);

    // Specify window size
    wresize(window, WINDOW_HEIGHT, WINDOW_WIDTH);

    /* Draw edges */
    // Horizontal
    for (unsigned i = 0; i < WINDOW_WIDTH; i++)
    {
        mvprintw(0, i, "X");
        mvprintw(WINDOW_HEIGHT - 1, i, "X");
    }

    // Vertical
    for (unsigned i = 0; i < WINDOW_HEIGHT; i++)
    {
        mvprintw(i, 0, "X");
        mvprintw(i, WINDOW_WIDTH - 1, "X");
    }
    refresh();
}

void Screen::updateScreen()
{
    for (unsigned i = 0; i < oldX.size(); i++)
    {
        mvwprintw(window, oldY[i], oldX[i], " ");
    }
    oldX.clear();
    oldY.clear();
    for (auto i = 0; i < NUM_OF_BALLS; i++)
    {
        if (curCoords->ballsX[i])
        {
            mvwprintw(window, curCoords->ballsY[i], curCoords->ballsX[i], "O");
            oldX.push_back(curCoords->ballsX[i]);
            oldY.push_back(curCoords->ballsY[i]);
        }
    }
    refresh();
}
