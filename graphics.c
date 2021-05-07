#include "graphics.h"
#include "logic.h"

//Window and renderer used by SDL.
//Quit is used in main to determine when to end the program or pause.
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
int quit = 1;

//Initialises the window and renderer.
//Returns 0 on success, 1 on failure.
int initialiseWindow()
{
    //Checks if there is a problem initialising SDL.
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s",
                     SDL_GetError());
        return EXIT_FAILURE;
    }
    //Window width and height.
    windowWidth = ((int) grid.width * GRID_CELL_SIZE) + 1;
    windowHeight = ((int) grid.height * GRID_CELL_SIZE) + 1;

    window = SDL_CreateWindow("Conway's Game of Life", 0, 0, windowWidth, windowHeight,
                              SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_ShowWindow(window);
    return 0;
}

//Renders the grid onto the window.
void render()
{
    //Dark colours for the grid.
    //Black and dark grey.
    SDL_Color background = {21, 21, 21, 255};
    SDL_Color gridLines = {44, 44, 44, 255};
    SDL_Color aliveCell = {255, 255, 255, 255};

    //Colour the background.
    SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b,
                           background.a);
    SDL_RenderClear(renderer);

    //Set the colour for the grid lines.
    SDL_SetRenderDrawColor(renderer, gridLines.r, gridLines.g, gridLines.b, gridLines.a);

    //Draw the grid lines.
    for (int x = 0; x < 1 + grid.width * GRID_CELL_SIZE; x += GRID_CELL_SIZE) {
        SDL_RenderDrawLine(renderer, x, 0, x, windowHeight);
    }
    for (int y = 0; y < 1 + grid.height * GRID_CELL_SIZE;
         y += GRID_CELL_SIZE) {
        SDL_RenderDrawLine(renderer, 0, y, windowWidth, y);
    }

    SDL_SetRenderDrawColor(renderer, aliveCell.r, aliveCell.g, aliveCell.b, aliveCell.a);
    //Draw the alive cells in white.
    for(int y = 0; y < grid.height; y++)
    {
        for(int x = 0; x < grid.width; x++)
        {
            //Creates a white rectangle in the position of the alive cell.
            if(grid.cells[y][x].state == true)
            {
                SDL_Rect rect = {
                        x * GRID_CELL_SIZE,
                                 y * GRID_CELL_SIZE,
                                 GRID_CELL_SIZE,
                                 GRID_CELL_SIZE
                };
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    //Presents the rendered image onto the window.
    SDL_RenderPresent(renderer);
}

//Checks for user input.
//Ends the program if the user closes the window.
//Pauses the game if the user presses return.
void checkEvents()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                quit = 0;
                break;
            case SDL_KEYDOWN:
                keypress(event.key.keysym.sym);
                break;
        }
    }
}

//Pauses the game if the user presses return.
void keypress(SDL_Keycode key)
{
    switch(key)
    {
        case SDLK_RETURN:
            if(quit == 1)
            {
                quit = 2;
            }
            else
            {
                quit = 1;
            }
            break;
    }
}

//Frees the memory used by SDL.
void cleanup()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}