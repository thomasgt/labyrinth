// maze.c
// Implementation of maze module.
// Defines maze utilities.

#include "maze.h"
#include <stdlib.h>

typedef struct rand_stack {
    uint8_t **data;
    uint32_t length;
    uint32_t capacity;
} rand_stack_t;

static rand_stack_t new_rand_stack(uint32_t reserve);
static void rand_stack_push(rand_stack_t *rs, uint8_t *val);
static uint8_t *rand_stack_pop(rand_stack_t *rs);
static void free_rand_stack(rand_stack_t *rs);

maze_t new_maze(uint32_t rows, uint32_t cols) {
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
    free(&maze->cells[0][0]);

    // Free the row pointers
    free(maze->cells);

    // Clear the rows and cols
    maze->n_rows = 0;
    maze->n_cols = 0;
}


int init_maze_prim(maze_t *maze) {
    // Check the input maze
    if (!maze) {
        return 1;
    } else if (maze.n_rows == 0 || maze.n_cols == 0) {
        return 1;
    } else if (!maze.cells) {
        return 1;
    }

    // Initialize all cells as walls
    for (int r = 0; r < maze.n_rows; ++r) {
        for (int c = 0; c < maze.n_cols; ++c) {
            maze.data[r][c] = CELL_WALL;
        }
    }

    // TODO Create a data structure that can remove the random element easily
    // LIRO - last in -- random out
    return 0;
}


static rand_stack_t new_rand_stack(uint32_t reserve) {
    rand_stack_t rs;

    // Reserve space for the specified number of elements
    rs.data = malloc(sizeof(uint8_t *) * reserve);
    
    // Initialize data structure members
    rs.length = 0;
    rs.capacity = reserve;

    return rs;
}


static void rand_stack_push(rand_stack_t *rs, uint8_t *val) {
    // Make sure the data structure exists
    if (!rs) {
        return;
    }


}


static uint8_t *rand_stack_pop(rand_stack_t *rs) {

}


static void free_rand_stack(rand_stack_t *rs) {

}


