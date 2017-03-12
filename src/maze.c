// maze.c
// Implementation of maze module.
// Defines maze utilities.

#include "maze.h"
#include <stdlib.h>
#include <time.h>


typedef struct cell {
    uint32_t row;
    uint32_t col;
} cell_t;


typedef struct wall {
    uint8_t *separated[2]
    uint8_t *cell;
} wall_t;


typedef struct wall_set {
    wall_t *walls;
    uint32_t length;
    uint32_t capacity;
} wall_set_t;


static wall_set_t wall_set_new(uint32_t reserve);
static void wall_set_push(wall_set_t *ws, wall_t wall);
static wall_t wall_set_pop(wall_set_t *ws);
static void free_rand_stack(wall_set_t *ws);


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



wall_set_t wall_set_new(uint32_t reserve) {
    wall_set_t ws;

    ws.length = 0;
    ws.capacity = reserve;
    ws.walls = malloc(reserve * sizeof(wall_t));

    return ws;
}


void wall_set_push(wall_set_t *rs, wall_t wall) {
    // Make sure the data structure exists
    if (!ws) {
        return;
    }

    // Make sure there's capacity
    // TODO Implement resizing
    if (ws->length == ws->capacity) {
        return;
    }

    // Insert the value and increment the index
    ws->walls[ws->length++] = wall;
}


wall_t wall_set_pop(wall_set_t *ws) {
    // Make sure the data structure exists
    if (!ws) {
        return NULL;
    }

    // Make sure there's data to pop
    if (ws->length == 0) {
        return NULL;
  }

    // Select a random value
    int rand_idx = rand() % ws->length;
    wall_t ret = ws->walls[rand_idx];

    // Replace the value with the one at the end
    ws->walls[rand_idx] = ws->walls[--ws->length];

    return ret;
}


void free_wall_set(wall_set_t *ws) {
    // Make sure the data structure exists
    if (!ws) {
        return;
    }

    // Clear the struct's members
    ws->capacity = 0;
    ws->length = 0;

    // Deallocate the structs memory
    free(ws->walls);
}

