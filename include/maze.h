// maze.h
// Header for maze module.
// Declares the maze data structure and utiltiies.

#include <stdint.h>

enum cell_states {
    CELL_WALL,
    CELL_OPEN,
    CELL_PATH,
    CELL_NUM_STATES
};


typedef struct maze {
    int n_rows;
    int n_cols;
    int **cells;
} maze_t;


maze_t maze_new(int rows, int cols);
void maze_free(maze_t *maze);

int maze_init_prim(maze_t *maze);

