#ifndef GAMEOFLIFE_FILEHANDLER_H
#define GAMEOFLIFE_FILEHANDLER_H
#include <stdio.h>

//Writes the final state of the game of life into a file.
int writeState(FILE *file);

//Reads the initial state of the game of life into the program.
int readState(FILE *file);

#endif //GAMEOFLIFE_FILEHANDLER_H
