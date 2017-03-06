// main.c

#include <stdio.h>
#include "maze.h"

int main(int argc, char *argv[]) {
    printf("Creating a new maze...\n");
    maze_t maze = new_maze(1024, 1024, CELL_BLOCKED);
    maze.cells[1][1] = CELL_OPEN;
    free_maze(&maze);
    return 0;
}
