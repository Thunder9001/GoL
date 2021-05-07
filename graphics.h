
#ifndef GAMEOFLIFE_GRAPHICS_H
#define GAMEOFLIFE_GRAPHICS_H

#include <SDL2/SDL.h>

//Initialises the window and renderers in SDL.
int initialiseWindow();

//Displays the grid onto the window.
void render();

//Checks for if the user has closed the program or paused the game.
void checkEvents();

//Used in check events to check for the user wanting to pause the game.
void keypress(SDL_Keycode key);

//Frees the memory.
void cleanup();

//Variables used to control the size of the window and cells.
static const int GRID_CELL_SIZE = 20;
int windowHeight;
int windowWidth;
//Quit variable.
extern int quit;

#endif //GAMEOFLIFE_GRAPHICS_H
