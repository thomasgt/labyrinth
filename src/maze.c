// maze.c
// Implementation of maze module.
// Defines maze utilities.

#include "maze.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


typedef struct frontier {
    int cell_r;
    int cell_c;
    int *cell;
    int *wall;
} frontier_t;


typedef struct frontier_set {
    int length;
    int capacity;
    frontier_t *frontiers;
} frontier_set_t;


static frontier_set_t fs_new(int reserve);
static void fs_add(frontier_set_t *fs, frontier_t f);
static int fs_get(frontier_set_t *fs, frontier_t *f);
static void fs_free(frontier_set_t *fs);


typedef struct neighbour_list {
    int length;
    frontier_t frontiers[4];
} neighbour_list_t;


static int nl_populate(neighbour_list_t *nl, int r, int c, maze_t *m);


maze_t maze_new(int rows, int cols) {
    // Create a maze to return
    maze_t maze;
    maze.n_rows = rows;
    maze.n_cols = cols;

    // Allocate the cells
    int *cells = malloc(rows * cols * sizeof(int));

    // Allocate pointers to each row
    maze.cells = malloc(rows * sizeof(int *));

    // Setup the pointers to the rows
    for (int r = 0; r < rows; ++r) {
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

    srand(time(NULL));

    // Initialize all cells as walls
    for (int r = 0; r < maze->n_rows; ++r) {
        for (int c = 0; c < maze->n_cols; ++c) {
            maze->cells[r][c] = CELL_WALL;
        }
    }

    // Start with a random cell
	int row = rand() % maze->n_rows;
	int col = rand() % maze->n_cols;

	// Get the neighbours
	neighbour_list_t nl;
	nl_populate(&nl, row, col, maze);

	// Put the neighbours into a frontier set
	frontier_set_t fs = fs_new(maze->n_rows * maze->n_cols / 2);
	for (int i = 0; i < nl.length; ++i) {
        fs_add(&fs, nl.frontiers[i]);
	}

	// Run the algorithm
	frontier_t f;
	while (fs_get(&fs, &f)) {
        if (*f.cell == CELL_WALL && *f.wall == CELL_WALL) {
            // Turn the frontier and wall into a path
            *f.cell = CELL_OPEN;
            *f.wall = CELL_OPEN;
            // Get the frontier's neighbours
            nl_populate(&nl, f.cell_r, f.cell_c, maze);
            // Add the neighbours to the frontier set
            for (int i = 0; i < nl.length; ++i) {
                fs_add(&fs, nl.frontiers[i]);
            }
        }

        // TODO Print the maze
	}



	fs_free(&fs);

    return 0;
}



frontier_set_t fs_new(int reserve) {
    frontier_set_t fs;

    fs.length = 0;
    fs.capacity = reserve;
    fs.frontiers = malloc(reserve * sizeof(frontier_t));

    return fs;
}


void fs_add(frontier_set_t *fs, frontier_t f) {
    // Make sure the data structure exists
    if (!fs) {
        return;
    }

    // Make sure there's capacity
    // TODO Implement resizing
    if (fs->length == fs->capacity) {
        return;
    }

    // Insert the value and increment the index
    fs->frontiers[fs->length++] = f;
}

// Returns the number of frontiers returned (0 or 1)
int32_t fs_get(frontier_set_t *fs, frontier_t *f) {
    // Make sure the data structure exists
    if (!fs) {
        return 0;
    }

    // Make sure there's data to pop
    if (fs->length == 0) {
        return 0;
    }

    // Select a random value
    int rand_idx = rand() % fs->length;
    *f = fs->frontiers[rand_idx];

    // Replace the value with the one at the end
    fs->frontiers[rand_idx] = fs->frontiers[--fs->length];

    return 1;
}


void fs_free(frontier_set_t *fs) {
    // Make sure the data structure exists
    if (!fs) {
        return;
    }

    // Clear the capacity and length
    fs->capacity = 0;
    fs->length = 0;

    // Deallocate the frontiers
    free(fs->frontiers);
}

// Returns the number of neighbours found
static int nl_populate(neighbour_list_t *nl, int r, int c, maze_t *m) {
    // Check for NULL pointers
    if (!nl || !m) {
        return 0;
    }

    // Clear the length of the neighbour list
    nl->length = 0;

    // Make sure the row and column are in bounds
    if (r < 0 || r >= m->n_rows) {
        return 0;
    } else if (c < 0 || c >= m->n_cols) {
        return 0;
    }

    // Fill in the neighbours
    // North
    if (r - 2 > 0) {
        if (m->cells[r - 1][c] == CELL_WALL && m->cells[r - 2][c] == CELL_WALL) {
            nl->frontiers[nl->length].wall = &m->cells[r - 1][c];
            nl->frontiers[nl->length].cell_r = r - 2;
            nl->frontiers[nl->length].cell_c = c;
            nl->frontiers[nl->length++].cell = &m->cells[r - 2][c];
        }
    }

    // East
    if (c + 2 < m->n_cols - 1) {
        if (m->cells[r][c + 1] == CELL_WALL && m->cells[r][c + 2] == CELL_WALL) {
            nl->frontiers[nl->length].wall = &m->cells[r][c + 1];
            nl->frontiers[nl->length].cell_r = r;
            nl->frontiers[nl->length].cell_c = c + 2;
            nl->frontiers[nl->length++].cell = &m->cells[r][c + 2];
        }
    }

    // South
    if (r + 2 < m->n_rows - 1) {
        if (m->cells[r + 1][c] == CELL_WALL && m->cells[r + 2][c] == CELL_WALL) {
            nl->frontiers[nl->length].wall = &m->cells[r + 1][c];
            nl->frontiers[nl->length].cell_r = r + 2;
            nl->frontiers[nl->length].cell_c = c;
            nl->frontiers[nl->length++].cell = &m->cells[r + 2][c];
        }
    }

    // West
    if (c - 2 > 0) {
        if (m->cells[r][c - 1] == CELL_WALL && m->cells[r][c - 2] == CELL_WALL) {
            nl->frontiers[nl->length].wall = &m->cells[r][c - 1];
            nl->frontiers[nl->length].cell_r = r;
            nl->frontiers[nl->length].cell_c = c - 2;
            nl->frontiers[nl->length++].cell = &m->cells[r][c - 2];
        }
    }

    return nl->length;
}

