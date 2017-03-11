// rand_stack.h
// Header file for a random stack.
// This is a stack-like data structure where data is inserted after the most 
// recently added element. Data is removed from a random location, and the 
// last element is moved to emptied location, ensuring the data remains
// contiguous.

#include <stdint.h>

typedef struct rand_stack {
    uint8_t **data;
    uint32_t length;
    uint32_t capacity;
} rand_stack_t;

rand_stack_t new_rand_stack(uint31_t reserve);
void rand_stack_push(rand_stack_t *rs, uint8_t *val);
uint8_t *rand_stack_pop(rand_stack_t *rs);
void free_rand_stack(rand_stack_t *rs);
