#include <thread>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <random>
#include <time.h>
#include "Ball.h"

#define WINDOW_WIDTH 80
#define WINDOW_HEIGHT 35

int main()
{
    srand(time(0));

    Ball b;

    b.getHealth();

    WINDOW *window = initscr();
    noecho();
    curs_set(0);

    // Ustalenie rozmiarow okna programu
    wresize(window, WINDOW_HEIGHT, WINDOW_WIDTH);

    /* Rysowanie krawedzi */
    // Krawedzie poziome
    for (unsigned i = 0; i < WINDOW_WIDTH; i++)
    {
        mvprintw(0, i, "X");
        mvprintw(WINDOW_HEIGHT - 1, i, "X");
    }

    // Krawedzie pionowe
    for (unsigned i = 0; i < WINDOW_HEIGHT; i++)
    {
        mvprintw(i, 0, "X");
        mvprintw(i, WINDOW_WIDTH - 1, "X");
    }

    for (unsigned i = 0; i < 100; i++)
    {
        // clear();
        mvprintw(10, i, "Hello world!");
        sleep(1);
        refresh();
    }
    getch();
    endwin();

    return 0;
}
