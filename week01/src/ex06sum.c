#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int rand_interval(int min, int max);
int int_input(char* str, char* incorrect_msg, char* not_int_msg);

int main(void) {
    srand(time(0));

    int const MIN = 500;
    int const MAX = 1000;

    int a = rand_interval(MIN, MAX);
    int b = rand_interval(MIN, MAX);
    int sum = a + b;
    printf("%d + %d = ", a, b);

    char input[64] = {0};

    clock_t start = clock();
    fgets(input, sizeof(input) / sizeof(char), stdin);
    clock_t diff = clock() - start;

    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken: %d seconds %d milliseconds\n", msec / 1000, msec % 1000);

    int input_sum = int_input(input, "Incorrect value for sum", "Sum must be int");
    if (input_sum == sum) {
        puts("The result is correct");
    } else {
        puts("The result is incorrect");
    }

    return EXIT_SUCCESS;
}

int rand_interval(int min, int max) {
    int range = max - min;
    return min + rand() % (range + 1);
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
