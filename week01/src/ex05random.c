#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

#define PATH_SEPARATOR '\\'

int rand_interval(int min, int max);
int int_input(char* str, char* incorrect_msg, char* not_int_msg);

char* basename(char* path);

int main(int argc, char** argv) {
    if (argc != 3) {
        puts("Usage:");
        puts("======\n");

        printf("%s <min> <max>\n\n", basename(argv[0]));

        return EXIT_FAILURE;
    }

    int min = int_input(argv[1], "Incorrect value for min", "Min must be int");
    int max = int_input(argv[2], "Incorrect value for max", "Max must be int");

    int range = max - min;
    if (range + 1 > RAND_MAX) {
        puts("The range is too large!");
        return EXIT_FAILURE;
    }

    srand(time(0));
    printf("Integer in range [%d, %d]: %d\n", min, max, rand_interval(min, max));

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
    if (*endptr != '\0' || lval < INT_MIN || lval > INT_MAX) {
        fprintf(stderr, "%s\n", not_int_msg);
        exit(EXIT_FAILURE);
    }
    return (int) lval;
}

char* basename(char* path) {
    char* base = strrchr(path, PATH_SEPARATOR);

    if (base) {
        base++;
    } else {
        base = path;
    }

    return base;
}
