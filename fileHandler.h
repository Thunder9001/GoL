#ifndef GAMEOFLIFE_FILEHANDLER_H
#define GAMEOFLIFE_FILEHANDLER_H
#include <stdio.h>
#include "logic.h"

//The format of the txt file generated follows a similar format to the .rle format found on the conway life wiki.
//https://www.conwaylife.com/wiki/Run_Length_Encoded
//Writes the final state of the game of life into a file.
int writeState(FILE *file);

//Writes a visual representation of the cells into a txt file.
int writeGrid(FILE *file);

//Reads the initial state of the game of life into the program.
int readState(FILE *file);

extern int iterations;
extern int tickRate;
static const int BUFFER_SIZE = 200;
static const char* GAMEOFLIFE_FORMAT = "%u%[^0123456789]%n";
#endif //GAMEOFLIFE_FILEHANDLER_H
