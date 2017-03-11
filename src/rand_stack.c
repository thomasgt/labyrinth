// rand_stack.c
// Implementation of the random stack data structure

#include "rand_stack.h"

rand_stack_t new_rand_stack(uint31_t reserve) {
    rand_stack_t rs;

    rs.length = 0;
    rs.capacity = reserve;
    rs.data = malloc(reserve * sizeof(uint8_t *));

    return rs;
}


void rand_stack_push(rand_stack_t *rs, uint8_t *val) {
    // Make sure the data structure exists
    if (!rs) {
        return;
    }

    // Make sure there's capacity
    // TODO Implement resizing
    if (rs->length == rs->capacity) {
        return;
    }

    // Insert the value and increment the index
    rs->data[rs->length++] = val;
}


uint8_t *rand_stack_pop(rand_stack_t *rs) {
    // Make sure the data structure exists
    if (!rs) {
        return;
    }

    // Make sure there's data to pop
    if (rs->length == 0) {
        return;
    }

    // Select a random value
    int rand_idx = rand() % rs->length;
    uint8_t *ret = rs->data[rand_idx];

    // Replace the value with the one at the end
    rs->data[rand_idx] = rs->data[--rs->length];

    return ret;
}


void free_rand_stack(rand_stack_t *rs) {
    // Make sure the data structure exists
    if (!rs) {
        return;
    }

    // Clear the struct's members
    rs->capacity = 0;
    rs->length = 0;

    // Deallocate the structs memory
    free(rs->data);
}


