#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "array_export.h"

#define PATH_SEPARATOR '\\'

typedef struct CmdArgs CmdArgs;
struct CmdArgs {
    size_t array_size;
    int min;
    int max;
    bool need_float;
    bool filename_specified;
    char* filename;
};

enum CMD_ARGS {
    ARG_EXE_NAME,
    ARG_ARRAY_SIZE,
    ARG_MIN,
    ARG_MAX,
    ARG_NEED_FLOAT,
    ARG_FIRST_OPTIONAL,
    ARG_OUT_FILE = ARG_FIRST_OPTIONAL,
    NUM_OF_ARGS
};

CmdArgs parse_args(int argc, char** argv);
char* basename(char* path);

void print_usage(char* exe_name) {
    puts("Usage:");
    puts("======\n");

    printf("%s <array_size> <min> <max> int|float [<out_file>]\n\n",
           basename(exe_name));
}

void generate_int_array(CmdArgs args);
void generate_float_array(CmdArgs args);

int rand_interval(int min, int max);
double frand_interval(int min, int max);

size_t
array_size_input(char* str, char* incorrect_msg, char* not_array_size_msg);
int int_input(char* str, char* incorrect_msg, char* not_int_msg);

int main(int argc, char** argv) {
    CmdArgs args = parse_args(argc, argv);

    srand(time(0));

    if (args.need_float) {
        generate_float_array(args);
    } else {
        generate_int_array(args);
    }

    return EXIT_SUCCESS;
}

void generate_int_array(CmdArgs args) {
    printf("Generating int array (size: %zu, min: %d, max: %d)\n",
           args.array_size,
           args.min,
           args.max);

    if (!args.filename_specified) {
        args.filename = "data/int_array.dat";
    }

    errno = 0;
    FILE* fp = fopen(args.filename, "wb");
    if (!fp) {
        perror("cannot open file for writing");
        exit(EXIT_FAILURE);
    }

    ArrayFileInfo info = get_int_file_info(args.array_size);

    size_t success = 0;

    errno = 0;
    success = fwrite(&info, sizeof(info), 1, fp);
    if (!success) {
        fclose(fp);
        perror("file info could not be stored");
        exit(EXIT_FAILURE);
    }

    int* array = malloc(args.array_size * sizeof(int));
    if (!array) {
        fclose(fp);
        fputs("memory for the array could not be allocated", stderr);
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < args.array_size; i++) {
        array[i] = rand_interval(args.min, args.max);
    }

    errno = 0;
    success = fwrite(array, sizeof(int), args.array_size, fp);
    if (success != args.array_size) {
        free(array);
        fclose(fp);
        perror("the array could not be stored");
        exit(EXIT_FAILURE);
    }

    free(array);
    fclose(fp);
}

void generate_float_array(CmdArgs args) {
    printf("Generating float array (size: %zu, min: %d, max: %d)\n",
           args.array_size,
           args.min,
           args.max);

    if (!args.filename_specified) {
        args.filename = "data/float_array.dat";
    }

    errno = 0;
    FILE* fp = fopen(args.filename, "wb");
    if (!fp) {
        perror("cannot open file for writing");
        exit(EXIT_FAILURE);
    }

    ArrayFileInfo info = get_float_file_info(args.array_size);

    size_t success = 0;

    errno = 0;
    success = fwrite(&info, sizeof(info), 1, fp);
    if (!success) {
        fclose(fp);
        perror("file info could not be stored");
        exit(EXIT_FAILURE);
    }

    double* array = malloc(args.array_size * sizeof(double));
    if (!array) {
        fclose(fp);
        fputs("memory for the array could not be allocated", stderr);
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < args.array_size; i++) {
        array[i] = frand_interval(args.min, args.max);
    }

    errno = 0;
    success = fwrite(array, sizeof(double), args.array_size, fp);
    if (success != args.array_size) {
        free(array);
        fclose(fp);
        perror("the array could not be stored");
        exit(EXIT_FAILURE);
    }

    free(array);
    fclose(fp);
}

int rand_interval(int min, int max) {
    int range = max - min;
    return min + rand() % (range + 1);
}

double frand_interval(int min, int max) {
    int range = max - min;
    return min + (double)rand() / RAND_MAX * range;
}

CmdArgs parse_args(int argc, char** argv) {
    CmdArgs args = {0};

    if (argc < ARG_FIRST_OPTIONAL || argc > NUM_OF_ARGS) {
        print_usage(argv[ARG_EXE_NAME]);
        exit(EXIT_FAILURE);
    }

    args.array_size = array_size_input(argv[ARG_ARRAY_SIZE],
                                       "Incorrect value for array size",
                                       "Size must be larger than 0");
    args.min =
      int_input(argv[ARG_MIN], "Incorrect value for min", "Min must be int");
    args.max =
      int_input(argv[ARG_MAX], "Incorrect value for max", "Max must be int");

    args.need_float = false;
    if (!strcmp(argv[ARG_NEED_FLOAT], "float")) {
        args.need_float = true;
    } else if (strcmp(argv[ARG_NEED_FLOAT], "int")) {
        print_usage(argv[ARG_EXE_NAME]);
        exit(EXIT_FAILURE);
    }

    args.filename_specified = (argc > ARG_OUT_FILE);
    args.filename = argv[ARG_OUT_FILE];

    return args;
}

size_t
array_size_input(char* str, char* incorrect_msg, char* not_array_size_msg) {
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
    if (*endptr != '\0' || lval < 1 || lval > INT_MAX) {
        fprintf(stderr, "%s\n", not_array_size_msg);
        exit(EXIT_FAILURE);
    }
    return (size_t)lval;
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
    return (int)lval;
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
