#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "array.h"

enum {
    N_RAND_VALS = ARRAY_CHUNK_SIZE + 10,
    MIN_RAND_VAL = 0,
    MAX_RAND_VAL = 10,
};

bool rand_fill_int_array(Array* array, size_t n_elems);
void print_int_array(Array* array);

int rand_interval(int min, int max);

int main(void) {
    Array* array = new_array(sizeof(int));
    if (!array) {
        fputs("memory for the array could not be allocated", stderr);
        return EXIT_FAILURE;
    }

    srand(time(0));

    bool success = rand_fill_int_array(array, N_RAND_VALS);
    if (!success) {
        fprintf(stderr, "array could not be filled with %d values\n", N_RAND_VALS);
        return EXIT_FAILURE;
    }

    int val = 255;
    array_set(array, 4, &val);

    print_int_array(array);

    free_array(array);

    return EXIT_SUCCESS;
}

bool rand_fill_int_array(Array* array, size_t n_elems) {
    for (size_t i = 0; i < n_elems; i++) {
        int rand_val = rand_interval(MIN_RAND_VAL, MAX_RAND_VAL);
        bool success = array_append(array, &rand_val);
        if (!success) {
            return false;
        }
    }

    return true;
}

void print_int_array(Array* array) {
    int* item = array_get(array, 0);
    printf("[%d", *item);

    for (size_t i = 1; i < array->size; i++) {
        item = array_get(array, i);
        printf(", %d", *item);
    }

    printf("]\n");
}

int rand_interval(int min, int max) {
    int range = max - min;
    return min + rand() % (range + 1);
}
