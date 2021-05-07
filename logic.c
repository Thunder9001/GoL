#include "logic.h"
#include <stdlib.h>

//Ternary operator macro used to compute the maximum and minimum between two values.
//Preprocessor code for MIN and MAX from https://gcc.gnu.org/onlinedocs/gcc-3.4.6/gcc/Min-and-Max.html
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))
struct Grid grid;

//Returns 0 on successful memory allocation
//Returns 1 on failure to allocate, returns 2 on invalid parameters.
int createGrid(int x, int y)
{
    //Checks that the height and width of the grid are between min and max values.
    if((x < MIN_WIDTH) || (y < MIN_HEIGHT) || (x > MAX_WIDTH) || (y > MAX_HEIGHT))
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

//Returns 0 on successful check.
//Returns 1 on invalid parameters.
unsigned int checkNeighbours(int x, int y)
{
    //Checks the parameters x and y are within the boundaries of the grid.
    if((x < 0) || (x >= grid.width) || (y < 0) || (y >= grid.height))
    {
        return 1;
    }

    //Loops checking all the neighbours of the cell adding to the count.
    for(int i = MAX(x - 1, 0); i <= MIN(x+1, grid.width - 1); i++)
    {
        for(int j = MAX(y-1, 0); j <= MIN(y+1, grid.height - 1); j++)
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

//Returns 0 on successful change.
//Returns 1 on invalid parameters.
int setNextState(int x, int y)
{
    //Checks the parameters x and y are within the boundaries of the grid.
    if((x < 0) || (x >= grid.width) || (y < 0) || (y >= grid.height))
    {
        return 1;
    }

    //Changes the state of the cell based on the rules of the Game of Life.
    if(grid.cells[y][x].state == true)
    {
        //Rule 1 and Rule 3, set cells dead.
        if((grid.cells[y][x].neighbours < 1) || (grid.cells[y][x].neighbours > 3))
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

//Sets the next state for all the cells in the grid.
//Updates the neighbour value for all cells after changing all the states.
void updateGrid()
{
    for(int y = 0; y < grid.height; y++)
    {
        for(int x = 0; x < grid.width; x++)
        {
            setNextState(x,y);
        }
    }

    for(int y = 0; y < grid.height; y++)
    {
        for(int x = 0; x < grid.width; x++)
        {
            grid.cells[y][x].neighbours = 0;
            checkNeighbours(x,y);
        }
    }
}

//Returns 0 on success
//Returns 1 on failure.
int setInitialState(int x, int y, bool state)
{
    //Checks the parameters x and y are within the boundaries of the grid.
    if((x < 0) || (x >= grid.width) || (y < 0) || (y >= grid.height))
    {
        return 1;
    }
    grid.cells[y][x].state = state;
    return 0;
}

//Returns 0 on success
//Returns 1 on failure
int setInitialNeighbours()
{
    //Loops through the grid setting the initial values for the number of neighbours.
    for(int y = 0; y < grid.height; y++)
    {
        for(int x = 0; x < grid.width; x++)
        {
            if (checkNeighbours(x, y) == 1)
                return 1;
        }
    }
    return 0;
}

//Frees memory used by the grid struct.
void destroyGrid()
{
    for(int i = 0; i < grid.height; i++)
    {
        free(grid.cells[i]);
    }
    free(grid.cells);
}