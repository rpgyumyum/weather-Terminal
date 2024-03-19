#include "nim-algo.h"

/* The algorithm modifies a pile array(number of untouched objects in each row) */
/* so what we do is generate the pile from the pyramid and then make a decision */
/* we then have to modify the pyramid based on the pile and send that back into the game loop. */

int oldPile[MAX_ROWS] = {1, 2, 3, 4, 5};
int oldPileN = sizeof(oldPile)/sizeof(oldPile[0]);

int calculateNimSum(int arr[], int n) 
{
    int nimSum = 0;
    
    for (int i = 0; i < n; i++) {
        nimSum ^= arr[i];
    }
    
    return nimSum;
}

void writeOldPile(int* pile)
{
    for (int i = 0; i < MAX_ROWS; i++) 
    {
        oldPile[i] = pile[i];
    }
}


void generatePile(int pyramid[MAX_ROWS][MAX_COLS], int* pile)
{
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLS; j++)
        {
            if(pyramid[i][j] == 1) pile[i]++;
        }
    }
}

void modifyPyramidFromPile(int* pile, int pyramid[MAX_ROWS][MAX_COLS])
{
    int mod_cnt, pile_diff;

    for (int i = 0; i < MAX_ROWS; i++)
    {
        if(pile[i] != oldPile[i])
        {
            pile_diff = oldPile[i] - pile[i];
            mod_cnt = 0;

            for (int j = 0; j < MAX_COLS; j++)
            {
                if(pyramid[i][j] == 1)
                {
                    pyramid[i][j] = 2;
                    mod_cnt++;

                    if (mod_cnt >= pile_diff)
                    {
                        //copy array
                        for (int k = 0; k < MAX_ROWS; k++) 
                        {
                            oldPile[k] = pile[k];
                        }

                        return;
                    }
                }
            }

            return; //unreachable 
                
        } 
    }
}


void makeOptimalMove(int* pile, int n) 
{
    int nimSum = calculateNimSum(pile, n);

    if (nimSum == 0) 
    {
        // in a losing position, make any move.
        for (int i = 0; i < n; i++) 
        {
            if (pile[i] > 0) 
            {
                pile[i]--;
                break;
            }
        }
    } 
    else 
    {
        //in a winning position, make a move to set Nim Sum to zero.
        for (int i = 0; i < n; i++) 
        {
            int newXOR = nimSum ^ pile[i];

            if (newXOR < pile[i] && pile[i] - newXOR >= 1) 
            {
                pile[i] = newXOR;
                break;
            }
        }
    }
}
