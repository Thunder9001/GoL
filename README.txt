Git URL: https://gitlab.com/sc20dkvp/sc20dkvp-gol

Git commit history in the commitHistory.txt file.

My implementation of Conway's game of life.
Press Enter/Return to pause/play the game.

Input the initial state for the game in the input.txt file.
There are two output files:
outputState.txt outputs into the same format as the input excluding iterations and tickrate.
outputGrid.txt outputs the dimensions of the grid and a representation of the grid with 0s and 1s.
0s being dead cells, and 1s being alive cells.

File input follows this format:
Iterations/Tick rate
Width/Height
2a38d
4a36d


Iterations must not be greater than 100.
Tick rate is in ms and must be between 200 and 1000ms
Width must be between 100 and 40
Height must be between 50 and 10

a stands for alive cells
d stands for dead cells
The numbers must add up to the specified width with a new line for every new row in the grid.