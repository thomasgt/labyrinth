// maze.c
// Implementation of maze module.
// Defines maze utilities.

#include "maze.h"
#include <stdlib.h>
#include <time.h>


maze_t maze_new(uint32_t rows, uint32_t cols) {
    // Create a maze to return
    maze_t maze;
    maze.n_rows = rows;
    maze.n_cols = cols;

    // Allocate the cells
    uint8_t *cells = malloc(rows * cols * sizeof(uint8_t));

    // Allocate pointers to each row
    maze.cells = malloc(rows * sizeof(uint8_t *));

    // Setup the pointers to the rows
    for (uint32_t r = 0; r < rows; ++r) {
        maze.cells[r] = &cells[r * cols];
    }

    return maze;
}


void maze_free(maze_t *maze) {
    // Free the cells
    free(&maze->cells[0][0]);

    // Free the row pointers
    free(maze->cells);

    // Clear the rows and cols
    maze->n_rows = 0;
    maze->n_cols = 0;
}


int maze_init_prim(maze_t *maze) {
    // Check the input maze
    if (!maze) {
        return 1;
    } else if (maze->n_rows == 0 || maze->n_cols == 0) {
        return 1;
    } else if (!maze->cells) {
        return 1;
    }

    // Initialize all cells as walls
    for (int r = 0; r < maze->n_rows; ++r) {
        for (int c = 0; c < maze->n_cols; ++c) {
            maze->cells[r][c] = CELL_WALL;
        }
    }

    return 0;
}




