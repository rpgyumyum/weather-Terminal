#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "nim-algo.h"


int pyramid[MAX_ROWS][MAX_COLS] = {
    {0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 1, 0, 1, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1}
};






void drawPyramid(int* posy, int* posx) 
{
    for (int row = 0; row < MAX_ROWS; row++) 
    {
        if (row == *posy) printw("--> ");

        for (int col = 0; col < MAX_COLS; col++) 
        {
            if (pyramid[row][col] == 0) printw(" ");
            else if (pyramid[row][col] == 2)
            {
                if (has_colors()) 
                {
                    attron(A_STANDOUT); // Enable strikethrough
                }

                printw("|");
                refresh();

                if (has_colors()) {
                    attroff(A_STANDOUT); // Disable strikethrough
                }
            }
            else if (*posx == col && *posy == row) printw("T");
            else printw("|");

        }
        printw("\n");
    }
}


void strikeRow(int* startInsert, int* endInsert, int* row)
{
    if (startInsert < endInsert)
    {
        for(int i = 0; i < MAX_COLS; i++)
        {
            if(i >= *startInsert && i <= *endInsert && pyramid[*row][i] == 1) pyramid[*row][i] = 2;
        }
    }
    else if (startInsert > endInsert)
    {
        for(int i = 0; i < MAX_COLS; i++)
        {
            if(i <= *startInsert && i >= *endInsert && pyramid[*row][i] == 1) pyramid[*row][i] = 2;
        }
    }
    
}


void moveLeft(int* col, int* row)
{
    for (int i = *col - 1; i >= 0; i--)
    {
        if (pyramid[*row][i] == 1)
        {
            *col = i;
            return;
        }
    }
}

void moveRight(int* col, int* row)
{
    for (int i = *col + 1; i < MAX_COLS; i++)
    {
        if (pyramid[*row][i] == 1)
        {
            *col = i;
            return;
        }
    }
}

void moveDown(int* row)
{
    for(int i = *row + 1; i < MAX_ROWS; i++)
    {
        for(int j = 0; j < MAX_COLS; j++)
        {
            if (pyramid[i][j] == 1) 
            {
                *row = i;
                return;
            }
        }
    }

}

void moveUp(int* row)
{
    for(int i = *row - 1; i >= 0; i--)
    {
        for(int j = 0; j < MAX_COLS; j++)
        {
            if (pyramid[i][j] == 1) 
            {
                *row = i;
                return;
            }
        }
    }
}

void movCol(int* col, int* row)
{
    for (int i = 0; i < MAX_COLS; i++)
    {
        if (pyramid[*row][i] == 1)
        {
            *col = i;
            return;
        }
    }
}

void movRow(int* col, int* row)
{
    for (int i = 0; i < MAX_ROWS; i++) 
    {
        for (int j = 0; j < MAX_COLS; j++) 
        {
            if (pyramid[i][j] == 1)
            {
                *row = i;
                *col = j;
                return;
            }
        }
    }

}


int checkLoss(void)
{
    for (int row = 0; row < MAX_ROWS; row++) 
    {
        for (int col = 0; col < MAX_COLS; col++) 
        {
            if (pyramid[row][col] == 1) return 0;
        }
    }

    return 1;
}

void resetGame(int* player) 
{
    int initialPyramid[MAX_ROWS][MAX_COLS] = 
    {
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 1}
    };

    // Copy the initial values back to the pyramid array
    for (int row = 0; row < MAX_ROWS; row++) 
    {
        for (int col = 0; col < MAX_COLS; col++) 
        {
            pyramid[row][col] = initialPyramid[row][col];
        }
    }

    *player = rand() & 1; // which player is playing currently 


}


int main(void) 
{
    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    noecho();
    srand(time(NULL));

    int row = 0, col = 4; //indicate pointer position
    int inInsert = 0; // boolean if in insert mode
    int startInsert = 0, endInsert = 0; //the two coordinates where we started and ended our insert
    
    

    int player = rand() & 1; // which player is playing currently 

    while (1) 
    {
        clear();
        printw("Nim Game\n");
        printw("Use arrow keys to select a line to remove and press space move to the line to which you want to remove to and press space again\n");
        printw("Press 'q' to quit.\n\n");

        int pile[MAX_ROWS] = {0};
        generatePile(pyramid, pile);


        if (player == 0) 
        {
            printw("Player's turn\n\n");

            drawPyramid(&row, &col);

            int ch = getch();

            if (ch == KEY_DOWN) 
            {
                moveDown(&row);
                movCol(&col, &row);
                inInsert = 0; //if we move up or down break out of insert mode
            }
            else if (ch == KEY_UP) 
            {
                moveUp(&row);
                movCol(&col, &row);
                inInsert = 0;
            } 
            else if (ch == KEY_LEFT)
            {
                moveLeft(&col, &row); 
            }
            else if (ch == KEY_RIGHT)
            {
                moveRight(&col, &row); 
            }
            else if (ch == ' ')
            {
                if (inInsert == 0)//if we arent in inser mode go into it
                {
                    inInsert = 1;
                    startInsert = col;
                }
                else if (inInsert == 1)//if we are in insert mode strike the selected lines and move to a valid position
                {
                    endInsert = col;
                    strikeRow(&startInsert, &endInsert, &row);
                    player = 1;
                    inInsert = 0;
                    writeOldPile(pile);
                    movRow(&col, &row);
                    movCol(&col, &row);
                }
            }
            else if (ch == 'q') 
            {
                break;
            }
        }
        else if (player == 1)
        {
            makeOptimalMove(pile, MAX_ROWS);
            modifyPyramidFromPile(pile, pyramid);
            player = 0;
        }



        // Check for game over
        if(checkLoss())
        {
            clear();
            if(player == 0) printw("Player won\n");
            else printw("Computer won\n");

            printw("Do you wish to keep playing? (y/n)\n");
            char answer = getch();

            if(answer == 'y') resetGame(&player);
            else break;
        }
    }

    endwin();
    return 0;
}

