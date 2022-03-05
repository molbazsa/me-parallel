#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define PATH_SEPARATOR '\\'

int* crew_prefix_wrapper(int* array, size_t array_size);
void crew_prefix(int* input, size_t array_size, int* output);

char* basename(char* path);
void print_usage(char* exe_name);

int main(int argc, char** argv) {
    if (argc > 2) {
        print_usage(basename(argv[0]));
        return EXIT_FAILURE;
    }

    bool need_print = false;
    if (!strcmp(argv[1], "-p") || !strcmp(argv[1], "--print")) {
        need_print = true;
    } else if (strcmp(argv[1], "")) {
        print_usage(basename(argv[0]));
        return EXIT_FAILURE;
    }

    int array[] = {1, 2, 3, 4, 5};
    size_t array_size = sizeof(array) / sizeof(int);

    int* prefix = crew_prefix_wrapper(array, array_size);
    if (!prefix) {
        fputs("memory for the prefix array could not be allocated", stderr);
        return EXIT_FAILURE;
    }

    if (need_print) {
        printf("Prefix: [%d", prefix[0]);
        for (size_t i = 1; i < array_size; i++) {
            printf(", %d", prefix[i]);
        }
        puts("]");
    }

    free(prefix);

    return EXIT_SUCCESS;
}

int* crew_prefix_wrapper(int* array, size_t array_size) {
    int* result = malloc(array_size * sizeof(int));
    if (result) {
        crew_prefix(array, array_size, result);
    }
    return result;
}

void crew_prefix(int* input, size_t array_size, int* output) {
    if (array_size == 1) {
        *output = *input;
    } else {
        size_t array1_size = array_size / 2;
        size_t array2_size = array_size - array1_size;

        crew_prefix(input, array1_size, output);
        crew_prefix(input + array1_size, array2_size, output + array1_size);

        for (size_t i = array1_size; i < array_size; i++) {
            output[i] += output[array1_size - 1];
        }
    }
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

void print_usage(char* exe_name) {
    puts("Usage:");
    puts("======\n");

    printf("%s [-p|--print]\n\n", exe_name);
}
