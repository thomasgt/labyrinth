// main.c

#include <stdio.h>
#include "maze.h"

int main(int argc, char *argv[]) {
    printf("Creating a new maze...\n");
    maze_t maze = maze_new(1001, 1001);
	maze_init_prim(&maze);
	FILE *fout = fopen("test.dat", "wb");
	fwrite(&maze.cells[0][0], sizeof(int), maze.n_rows * maze.n_cols, fout);
	fclose(fout);
    maze_free(&maze);
    return 0;
}
