// maze.c
// Implementation of maze module.
// Defines maze utilities.

#include "maze.h"

maze_t new_maze(uint32_t rows, uint32_t cols, uint8_t default_val) {
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

void free_maze(maze_t *maze) {
    // Free the cells
    free(maze->cells[0][0]);

    // Free the row pointers
    free(maze->cells);

    // Clear the rows and cols
    maze->n_rows = 0;
    maze->n_cols = 0;
}

