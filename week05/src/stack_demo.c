#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

int main(void) {
    Stack* stack = new_stack(sizeof(int));
    if (!stack) {
        fputs("memory for the stack could not be allocated", stderr);
        return EXIT_FAILURE;
    }

    int items[] = {10, 15, 27, 55, 49};
    size_t n_items = sizeof(items) / sizeof(int);

    for (size_t i = 0; i < n_items; i++) {
        printf("Pushing %d (item %zu) to stack\n", items[i], i);
        bool success = stack_push(stack, &items[i]);
        if (!success) {
            fputs("cannot push item to stack", stderr);
            return EXIT_FAILURE;
        }
    }

    int top = *((int*)stack->top);
    printf("Item on the top of the stack is %d\n", top);

    int* item = stack_pop(stack);

    while (item) {
        printf("Popped %d from the stack\n", *item);
        item = stack_pop(stack);
    }

    free_stack(stack);

    return EXIT_SUCCESS;
}
