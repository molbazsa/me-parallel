#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
#include <limits.h>

#define NUM_OF_ELEMS 80000000
#define RANDOM_ARRAY
// #define PRINT_ARRAY

size_t size_t_input(char* str, char* incorrect_msg, char* not_int_msg);
int int_input(char* str, char* incorrect_msg, char* not_int_msg);
bool ask_for_random();
int rand_interval(int min, int max);

int sum_array(int* array, size_t num_of_elems);
int min_array(int* array, size_t num_of_elems);
int max_array(int* array, size_t num_of_elems);

int main(void) {
    srand(time(0));

    int const MIN = 500;
    int const MAX = 1000;

#ifdef NUM_OF_ELEMS
    size_t num_of_elems = NUM_OF_ELEMS;
    printf("Number of elements: %zu\n", num_of_elems);
#else
    char size_input[64] = {0};
    printf("Number of elements to store: ");
    fgets(size_input, sizeof(size_input) / sizeof(char), stdin);
    size_t num_of_elems = size_t_input(size_input, "Incorrect value for size", "Size must be of size_t type");
#endif // NUM_OF_ELEMS

    int* array = malloc(num_of_elems * sizeof(int));
    if (!array) {
        puts("Cannot allocate array");
        return EXIT_FAILURE;
    }

#ifdef RANDOM_ARRAY
    bool need_fill_random = true;
#else
    printf("Should the array be filled with random values (y/n)? ");
    bool need_fill_random = ask_for_random();
#endif // RANDOM_ARRAY

    if (need_fill_random) {
        for (size_t i = 0; i < num_of_elems; i++) {
            array[i] = rand_interval(MIN, MAX);
        }
    } else {
        for (size_t i = 0; i < num_of_elems; i++) {
            char input[64] = {0};
            printf("Int at index %d: ", i);
            fgets(input, sizeof(input) / sizeof(char), stdin);
            array[i] = int_input(input, "Incorrect value for element", "The element must be int");
        }
    }

#ifdef PRINT_ARRAY
    printf("[%d", array[0]);
    for (size_t i = 1; i < num_of_elems; i++) {
        printf(", %d", array[i]);
    }
    printf("]\n");
#endif // PRINT_ARRAY

    clock_t start = clock();
    int sum = sum_array(array, num_of_elems);
    clock_t diff = clock() - start;
    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken: %d seconds %d milliseconds\n", msec / 1000, msec % 1000);
    printf("Sum of the elements: %d", sum);

    return EXIT_SUCCESS;
}

size_t size_t_input(char* str, char* incorrect_msg, char* not_int_msg) {
    char* endptr = 0;
    errno = 0;
    long lval = strtol(str, &endptr, 0);
    if (errno != 0) {
        perror(incorrect_msg);
        exit(EXIT_FAILURE);
    }
    if (endptr == str) {
        fputs("No digits were found\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (*endptr != '\n' || lval < 0 || lval > SIZE_MAX) {
        fprintf(stderr, "%s\n", not_int_msg);
        exit(EXIT_FAILURE);
    }
    return (size_t) lval;
}

int int_input(char* str, char* incorrect_msg, char* not_int_msg) {
    char* endptr = 0;
    errno = 0;
    long lval = strtol(str, &endptr, 0);
    if (errno != 0) {
        perror(incorrect_msg);
        exit(EXIT_FAILURE);
    }
    if (endptr == str) {
        fputs("No digits were found\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (*endptr != '\n' || lval < INT_MIN || lval > INT_MAX) {
        fprintf(stderr, "%s\n", not_int_msg);
        exit(EXIT_FAILURE);
    }
    return (int) lval;
}

bool ask_for_random() {
    char input[3] = {0};
    fgets(input, sizeof(input) / sizeof(char), stdin);
    if (input[1] != '\n') {
        puts("Answer must be y/n");
        exit(EXIT_FAILURE);
    }
    switch (input[0]) {
        case 'y':
            return true;
        case 'n':
            return false;
        default:
            puts("Answer must be y/n");
            exit(EXIT_FAILURE);
    }
}

int rand_interval(int min, int max) {
    int range = max - min;
    return min + rand() % (range + 1);
}

int sum_array(int* array, size_t num_of_elems) {
    int sum = 0;

    for (size_t i = 0; i < num_of_elems; i++) {
        sum += array[i];
    }

    return sum;
}

int min_array(int* array, size_t num_of_elems) {}
int max_array(int* array, size_t num_of_elems) {}
