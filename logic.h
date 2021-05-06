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
static const int MAX_HEIGHT = 50;
static const int MAX_WIDTH = 100;
static const int MIN_HEIGHT = 10;
static const int MIN_WIDTH = 40;

//Creates a grid of cells based on the user input x and y.
//X and Y must both be between 40 and 100.
int createGrid(int x, int y);

//Checks the number of neighbours of the cell.
//Takes in the x and y value of the cell being checked.
//Returns a positive integer
unsigned int checkNeighbours(int x, int y);

//Function to set the next state of the cell at X and Y
//Implements the rules of the game of life.
int setNextState(int x, int y);

//Function to set the initial values of the grid.
int setInitialState(int x, int y, bool state);

//Sets the initial value for all the neighbours in the grid.
int setInitialNeighbours();

//Function to free the memory used by the grid.
void destroyGrid();

#endif //GAMEOFLIFE_LOGIC_H
