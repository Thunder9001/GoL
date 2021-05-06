#include "logic.h"
#include "graphics.h"
#include "fileHandler.h"

int errorCode = 0;

//Reads from the file and checks for errors.
//Displays the grid using the grid that has been read in.
//Update the grid every tick.
//On the final tick output to the file and display to the user.
int main(int argc, char *argv[])
{
    //File pointers for reading and writing the grid.
    FILE* read = fopen("../input.txt", "r");
    FILE* writeG= fopen("../outputGrid.txt", "w");
    FILE* writeS= fopen("../outputState.txt", "w");


    //Error messages which print out if there is a problem during the reading of the file.
    errorCode = readState(read);
    if(errorCode == 1)
    {
        printf("Error in opening the file. Ensure you have not deleted or moved input.txt.\n");
        return EXIT_FAILURE;
    }
    else if(errorCode == 2)
    {
        printf("Could not read the number of iterations, tickRate, height or width input. "
               "Please read the README the format.\n");
        return EXIT_FAILURE;
    }
    else if(errorCode == 3)
    {
        printf("Input for the number of iterations is too high, the number of iterations must be below 50.\n");
        return EXIT_FAILURE;
    }
    else if(errorCode == 4)
    {
        printf("The tickRate input is not between 200 and 1000ms.\n");
        return EXIT_FAILURE;
    }
    else if(errorCode == 5)
    {
        printf("The grid height and width is not an integer.\n");
        return EXIT_FAILURE;
    }
    else if(errorCode == 6)
    {
        printf("The number of cells specified in the input file does not match the grid width.\n");
        return EXIT_FAILURE;
    }
    else if(errorCode == 7)
    {
        printf("A cell has tried to be set which was out of bounds. Check your input file to see if"
               "the number of cells matches the width.\n");
        return EXIT_FAILURE;
    }
    else if(errorCode == 8)
    {
        printf("Invalid file format. Please follow the guide in the README.\n");
        return EXIT_FAILURE;
    }
    else if(errorCode == 9)
    {
        printf("The height and width of the grid are greater than the maximum.\n");
        return EXIT_FAILURE;
    }
    else if(errorCode == 10)
    {
        printf("There was a problem allocating memory to the grid.\n");
        return EXIT_FAILURE;
    }

    //Error messages if there are errors with setting the initial states.
    if(setInitialNeighbours() == 1)
    {
        printf("Error in setting the initial values for the program. Program will terminate.\n");
        return EXIT_FAILURE;
    }
    if(writeGrid(writeG) == 1)
        printf("Error in writing the grid to the file. File could not be saved.\n");
    if(writeState(writeS) == 1)
        printf("Error in writing the final state to the file. File could not be saved.\n");


    //Freeing the memory when the program finishes.
    fclose(read);
    fclose(writeG);
    fclose(writeS);
    destroyGrid();
    return 0;
}
