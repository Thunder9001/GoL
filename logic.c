#include "logic.h"
#include <stdlib.h>
#include <stdio.h>

//Ternary operator macro used to compute the maximum and minimum between two values.
#define MIN(X,Y) (X < Y ? X : Y)
#define MAX(X,Y) (X > Y ? X : Y)
struct Grid grid;

//Returns 0 on successful memory allocation
//Returns 1 on failure to allocate, returns 2 on invalid parameters.
int createGrid(int x, int y)
{
    //Checks that the height and width of the grid are
    if((x < MIN_WIDTH) | (y < MIN_HEIGHT) | (x > MAX_WIDTH) | (y > MAX_HEIGHT))
    {
        return 2;
    }
    grid.height = y;
    grid.width = x;

    //Allocates memory to all the cells in the grid.
    grid.cells = calloc(y, sizeof(struct Cell*));
    if(!grid.cells)
    {
        return 1;
    }
    for(int i = 0; i < y; i++)
    {
        grid.cells[i] = calloc(x, sizeof(struct Cell));
        if(!grid.cells[i])
        {
            return 1;
        }
    }
    return 0;
}

unsigned int checkNeighbours(int x, int y)
{
    //Checks the parameters x and y are within the boundaries of the grid.
    if((x < 0) | (x > grid.width) | (y < 0) | (y > grid.height))
    {
        return 1;
    }

    //Loops checking all the neighbours of the cell adding to the count.
    for(int i = MAX(x - 1, 0); i <= MIN(x+1, grid.width); i++)
    {
        for(int j = MAX(y-1, 0); j <= MIN(y+1, grid.height); j++)
        {
            //Adds to the counter if a neighbour is alive.
            if((grid.cells[j][i].state == true) && !((x == i) && (y == j)))
            {
                grid.cells[y][x].neighbours++;
            }
        }
    }

    return 0;
}

int setNextState(int x, int y)
{
    //Checks the parameters x and y are within the boundaries of the grid.
    if((x < 0) | (x > grid.width) | (y < 0) | (y > grid.height))
    {
        return 1;
    }

    //Changes the state of the cell based on the rules of the Game of Life.
    if(grid.cells[y][x].state == true)
    {
        //Rule 1 and Rule 3, set cells dead.
        if((grid.cells[y][x].neighbours < 1) | (grid.cells[y][x].neighbours > 3))
        {
            grid.cells[y][x].state = false;
        }

        //Rule 2, keep cells alive
        if((grid.cells[y][x].neighbours <= 3) && (grid.cells[y][x].neighbours >= 2))
        {
            grid.cells[y][x].state = true;
        }
    }
    //Rule 4, dead cell becomes alive.
    else if((grid.cells[y][x].state == false) && (grid.cells[y][x].neighbours == 3))
    {
        grid.cells[y][x].state = true;
    }

    return 0;
}
