#include "fileHandler.h"
#include <string.h>

int iterations = 0;
int tickRate = 0;

//Returns 0 on successful file write.
//Returns 1 on invalid file.
int writeState(FILE *file)
{
    //Checks if the file is open.
    if(file == NULL)
    {
        return 1;
    }

    //Writes the width and the height of the grid on the first line.
    fprintf(file,"%i/%i\n", grid.width, grid.height);

    //Counts the number of dead and alive cells.
    int countAlive = 0;
    int countDead = 0;

    //Loop to print out the cells state in the txt file.
    for(int y = 0; y < grid.height; y++)
    {
        for(int x = 0; x < grid.width; x++)
        {
            if(grid.cells[y][x].state == true)
            {
                if(countDead != 0)
                    fprintf(file, "%id", countDead);
                countDead = 0;
                countAlive++;
            }
            else
            {
                if(countAlive != 0)
                    fprintf(file,"%ia", countAlive);
                countAlive = 0;
                countDead++;
            }
        }
        if(countAlive != 0)
            fprintf(file,"%ia", countAlive);
        if(countDead != 0)
            fprintf(file, "%id", countDead);
        countAlive = 0;
        countDead = 0;
        fprintf(file, "\n");
    }

    return 0;
}

//Returns 0 on successful file write.
//Returns 1 on invalid file.
int writeGrid(FILE *file)
{
    //Checks if the file is open.
    if(file == NULL)
    {
        return 1;
    }

    //Writes the width and the height of the grid on the first line.
    fprintf(file,"%i/%i\n", grid.width, grid.height);

    //Writes the grid into the file.
    for(int y = 0; y < grid.height; y++)
    {
        for(int x = 0; x < grid.width; x++)
        {
            fprintf(file, "%i ", grid.cells[y][x].state);
        }
        fprintf(file, "\n");
    }

    return 0;
}

//Returns 0 on successful file read
//Returns 1-10 based on different errors.
int readState(FILE *file)
{
    //Checks if the file is open.
    if(file == NULL)
    {
        return 1;
    }

    //Temporary variables.
    unsigned int count;
    int height, width;
    char temp1[20];
    char temp2[20];
    char *ptr;
    char buffer[BUFFER_SIZE];

    //Reads in the number of iterations to run through, and the tick rate of the game.
    fgets(buffer, BUFFER_SIZE, file);
    if(2 != sscanf(buffer, "%[^/]/%s", temp1, temp2))
    {
        return 2;
    }
    iterations = (int) strtol(temp1, &ptr, 10);
    tickRate = (int) strtol(temp2, &ptr, 10);

    //Return error messages 3 and 4 if the tick rate or number of iterations input are too high
    if(iterations > 50)
    {
        return 3;
    }
    if((tickRate > 1000) || (tickRate < 200))
    {
        return 4;
    }

    //Reads in the width and height of the grid from the first line of the file.
    //Converts to an integer.
    fgets(buffer, BUFFER_SIZE, file);
    if(2 != sscanf(buffer, "%[^/]/%s", temp1, temp2))
    {
        return 2;
    }
    width = (int) strtol(temp1, &ptr,10);
    height = (int) strtol(temp2, &ptr, 10);

    //Checks if the input for the grid height and width is an integer.
    if((height == 0) || (width == 0))
        return 5;

    //Returns 9 if the height and width entered are greater than the maximum.
    //Returns 10 if there is a problem allocating memory.
    if(createGrid(width, height) == 2)
        return 9;
    else if(createGrid(width, height) == 1)
        return 10;

    //Reads in the lines containing the grid data.
    fgets(buffer, BUFFER_SIZE, file);
    for(int i = 0; i < height; i++)
    {
        //Removes the end line character
        buffer[strcspn(buffer, "\n")] = 0;

        //total_n used to store the pointer location for 'd' and 'a', where the next sscanf will begin.
        //n stores the end pointer location.
        //Start variable used to determine which cell to begin setting.
        //Count used to store the number of cells in a row with that state.
        int total_n = 0;
        int n;
        int start = 0;
        count = 0;

        //While loop ending when there is nothing left to read in.
        while (2 == sscanf(buffer + total_n, GAMEOFLIFE_FORMAT, &count, temp1, &n))
        {
            total_n += n;

            //Returns 6 if the number of cells does not match the grid width.
            if((start + count) > grid.width)
            {
                return 6;
            }

            //Sets the cells to dead if temp1 == 'd'
            if(strcmp(temp1, "d") == 0)
            {
                for(int j = start; j < start + count; j++)
                {
                    //Returns 7 if out of bounds.
                    if(setInitialState(j, i, false) == 1)
                        return 7;
                }
            }
            //Sets the cells to alive if temp1 == 'a'
            else if(strcmp(temp1, "a") == 0)
            {
                for(int j = start; j < start + count; j++)
                {
                    //Returns 7 if out of bounds.
                    if(setInitialState(j, i, true))
                        return 7;
                }
            }
            //Returns 8 for invalid file format. ie. Characters other than 'd' or 'a'
            else
                return 8;

            start += (int) count;
        }

        //Returns 6 if the number of cells does not match the grid width.
        if(start != grid.width)
        {
            return 6;
        }
        //Reads the next line.
        fgets(buffer, BUFFER_SIZE, file);
    }

    return 0;
}
