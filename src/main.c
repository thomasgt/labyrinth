// main.c

#include <stdio.h>
#include "maze.h"

int main(int argc, char *argv[]) {
    printf("Creating a new maze...\n");
    maze_t maze = maze_new(1024, 1024);
    maze.cells[1][1] = CELL_OPEN;
    maze_free(&maze);
    return 0;
}
