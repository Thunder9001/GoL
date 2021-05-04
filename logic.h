#ifndef GAMEOFLIFE_LOGIC_H
#define GAMEOFLIFE_LOGIC_H
#include <stdbool.h>
#include <stdlib.h>

//Cells store information on their current status and the number of neighbours.
//True for alive, False for dead.
struct Cell{
    bool state;
    unsigned int neighbours;
};

//Grid structure containing the dimensions of the game of life and all the cells.
struct Grid
{
    struct Cell** cells;
    unsigned int height;
    unsigned int width;
};

//Global grid.
extern struct Grid grid;

//Constants storing the maximum and minimum values.
static const int MAX_HEIGHT = 100;
static const int MAX_WIDTH = 100;
static const int MIN_HEIGHT = 40;
static const int MIN_WIDTH = 40;

//Creates a grid of cells based on the user input x and y.
//X and Y must both be between 40 and 100.
int createGrid(int x, int y);

//Checks the number of neighbours of the cell.
//Takes in the x and y value of the cell being checked.
//Returns a positive integer
unsigned int checkNeighbours(int x, int y);

int setNextState(int x, int y);

#endif //GAMEOFLIFE_LOGIC_H
