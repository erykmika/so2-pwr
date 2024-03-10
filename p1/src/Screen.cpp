#include "Screen.h"

Screen::Screen(Coords &coords)
{
    this->curCoords = coords;
    this->oldCoords = Coords();
    window = nullptr;
}

void Screen::initThread(Coords &coords)
{
    Screen scr(coords);
    std::thread scr_thread(&Screen::run, &scr);
    scr_thread.join();
}

void Screen::run()
{
    initScreen();
    getch();
    endwin();
}

void Screen::initScreen()
{
    WINDOW *window = initscr();
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
}
