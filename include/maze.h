// maze.h
// Header for maze module.
// Declares the maze data structure and utiltiies.

#include <stdint.h>

enum cell_states {
    CELL_BLOCKED,
    CELL_OPEN,
    CELL_PATH,
    CELL_NUM_STATES
}


typedef struct maze {
    uint32_t n_rows;
    uint32_t n_cols;
    uint8_t **cells;
} maze_t;

maze_t *new_maze(uint32_t rows, uint32_t cols, uint8_t default_val);
void free_maze(maze_t *maze);
