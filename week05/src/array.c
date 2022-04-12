#include <string.h>

#include "array.h"

bool extend_array(Array* array);

Array* new_array(size_t elem_size) {
    Array* array = malloc(sizeof(Array));
    if (!array) {
        return 0;
    }

    void* elements = malloc(ARRAY_CHUNK_SIZE * elem_size);
    if (!elements) {
        free(array);
        return 0;
    }

    array->elements = elements;
    array->elem_size = elem_size;
    array->size = 0;
    array->capacity = ARRAY_CHUNK_SIZE;

    return array;
}

void free_array(Array* array) {
    free(array->elements);
    free(array);
}

bool array_append(Array* array, void* element) {
    if (array->size == array->capacity) {
        bool success = extend_array(array);
        if (!success) {
            return false;
        }
    }

    char* dest = (char*) array->elements + (array->size * array->elem_size);
    memcpy(dest, element, array->elem_size);
    array->size++;

    return true;
}

bool extend_array(Array* array) {
    void* elements = 0;

    elements = malloc(2 * array->capacity * array->elem_size);

    if (elements) {
        array->capacity *= 2;
    } else {
        elements = malloc((array->capacity + ARRAY_CHUNK_SIZE) * array->elem_size);

        if (elements) {
            array->capacity += ARRAY_CHUNK_SIZE;
        } else {
            return false;
        }
    }

    char* src = (char*) array->elements;
    char* dest = (char*) elements;
    memcpy(dest, src, array->size * array->elem_size);

    free(array->elements);
    array->elements = elements;

    return true;
}

void* array_get(Array* array, size_t index) {
    char* elements_bytes = (char*) array->elements;
    return elements_bytes + index * array->elem_size;
}

void array_set(Array* array, size_t index, void* element) {
    char* dest = (char*) array->elements + (index * array->elem_size);
    memcpy(dest, element, array->elem_size);
}
