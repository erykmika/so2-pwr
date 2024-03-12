#include "Screen.h"

Screen::Screen(Data *data)
{
    curData = data;
    window = nullptr;
}

void Screen::run(Data *data)
{
    Screen scr(data);
    scr.initScreen();
    while (data->exit_flag != EXIT_KEY)
    {
        scr.updateScreen();
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(REFRESH_RATE));
        data->exit_flag = getch();
    }
    getch();
    endwin();
}

void Screen::initScreen()
{
    window = initscr();
    noecho();
    curs_set(0);
    nodelay(window, 1);

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
    // Update balls
    for (unsigned i = 0; i < oldX.size(); i++)
    {
        mvwprintw(window, oldY[i], oldX[i], " ");
    }
    oldX.clear();
    oldY.clear();
    for (auto i = 0; i < NUM_OF_BALLS; i++)
    {
        if (curData->ballsAlive[i])
        {
            mvwprintw(window, curData->ballsY[i], curData->ballsX[i], "O");
            oldX.push_back(curData->ballsX[i]);
            oldY.push_back(curData->ballsY[i]);
        }
    }

    refresh();

    // Update gray area
    if (oldGrayX)
    {
        for (uint8_t v = oldGrayY; v > oldGrayY - GRAY_HEIGHT; v--)
        {
            for (uint8_t h = oldGrayX; h < oldGrayX + GRAY_WIDTH; h++)
            {
                mvwprintw(window, v, h, " ");
            }
        }
    }

    refresh();

    if (curData->grayAlive)
    {
        for (uint8_t v = curData->grayY; v > curData->grayY - GRAY_HEIGHT; v--)
        {
            for (uint8_t h = curData->grayX; h < curData->grayX + GRAY_WIDTH; h++)
            {
                mvwprintw(window, v, h, "#");
            }
        }
    }

    oldGrayX = curData->grayX;
    oldGrayY = curData->grayY;

    // Refresh screen
    refresh();
}
