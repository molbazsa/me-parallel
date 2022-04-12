#include "stack.h"

Stack* new_stack(size_t elem_size) {
    Stack* stack = malloc(sizeof(Stack));
    if (!stack) {
        return 0;
    }

    Array* elements = new_array(elem_size);
    if (!elements) {
        free(stack);
        return 0;
    }

    stack->elements = elements;
    stack->size = 0;
    stack->top = 0;

    return stack;
}

void free_stack(Stack* stack) {
    free_array(stack->elements);
    free(stack);
}

bool stack_push(Stack* stack, void* element) {
    bool success = array_append(stack->elements, element);
    if (!success) {
        return false;
    }

    stack->size++;
    stack->top = array_get(stack->elements, stack->size - 1);

    return true;
}

void* stack_pop(Stack* stack) {
    if (stack->size == 0) {
        return 0;
    }

    stack->size--;
    stack->top = array_get(stack->elements, stack->size - 1);
    return array_get(stack->elements, stack->size);
}
