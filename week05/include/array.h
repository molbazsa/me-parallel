#ifndef GUARD_C68F2106_A7DD_45DB_B7FD_B752ABA9C497
#define GUARD_C68F2106_A7DD_45DB_B7FD_B752ABA9C497

#include <stdlib.h>
#include <stdbool.h>

enum {
    ARRAY_CHUNK_SIZE = 128,
};

typedef struct Array Array;
struct Array {
    void* elements;
    size_t elem_size;
    size_t size;
    size_t capacity;
};

Array* new_array(size_t elem_size);
void free_array(Array* array);

bool array_append(Array* array, void* element);
void* array_get(Array* array, size_t index);
void array_set(Array* array, size_t index, void* element);

#endif // GUARD_C68F2106_A7DD_45DB_B7FD_B752ABA9C497
