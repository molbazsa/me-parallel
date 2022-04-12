#ifndef GUARD_7AAB647F_0107_4347_A25C_1758990BC25C
#define GUARD_7AAB647F_0107_4347_A25C_1758990BC25C

#include <stdlib.h>
#include <stdbool.h>

#include "array.h"

typedef struct Stack Stack;
struct Stack {
    Array* elements;
    size_t size;
    void* top;
};

Stack* new_stack(size_t elem_size);
void free_stack(Stack* stack);

bool stack_push(Stack* stack, void* element);
void* stack_pop(Stack* stack);

#endif // GUARD_7AAB647F_0107_4347_A25C_1758990BC25C
