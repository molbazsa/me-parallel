#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "array_export.h"
#include "perf_timing.h"

#define ARRAY_FILENAME "data/int_array.dat"

#define PATH_SEPARATOR '\\'

typedef struct CmdArgs CmdArgs;
struct CmdArgs {
    bool need_print;
};

enum CMD_ARGS {
    ARG_EXE_NAME,
    ARG_NEED_PRINT,
    NUM_OF_ARGS,
};

CmdArgs parse_args(int argc, char** argv);
char* basename(char* path);

void print_usage(char* exe_name) {
    puts("Usage:");
    puts("======\n");

    printf("%s [-p|--print]\n\n", exe_name);
}

int* import_array(char* filename, ArrayFileInfo* info);

int* crew_prefix_wrapper(int* array, size_t array_size);
void crew_prefix(int* input, size_t array_size, int* output);

int main(int argc, char** argv) {
    CmdArgs args = parse_args(argc, argv);

    ArrayFileInfo info = {0};
    int* array = import_array(ARRAY_FILENAME, &info);
    size_t array_size = info.num_of_elems;

    int* prefix = crew_prefix_wrapper(array, array_size);

    free(array);

    if (args.need_print) {
        printf("Prefix: [%d", prefix[0]);
        for (size_t i = 1; i < array_size; i++) {
            printf(", %d", prefix[i]);
        }
        puts("]");
    }

    free(prefix);

    return EXIT_SUCCESS;
}

int* import_array(char* filename, ArrayFileInfo* info) {
    errno = 0;
    FILE* fp = fopen(filename, "rb");
    if (!fp) {
        perror("cannot open file for reading");
        exit(EXIT_FAILURE);
    }

    size_t success = 0;

    errno = 0;
    success = fread(info, sizeof(ArrayFileInfo), 1, fp);
    if (!success) {
        fclose(fp);
        perror("file info could not be read");
        exit(EXIT_FAILURE);
    }

    if (!is_compatible(*info) || !is_int_array(*info)) {
        fputs("the array file is incompatible", stderr);
        exit(EXIT_FAILURE);
    }

    int* array = malloc(info->num_of_elems * sizeof(int));
    if (!array) {
        fclose(fp);
        fputs("memory for the array could not be allocated", stderr);
        exit(EXIT_FAILURE);
    }

    errno = 0;
    success = fread(array, sizeof(int), info->num_of_elems, fp);
    if (success != info->num_of_elems) {
        free(array);
        fclose(fp);
        perror("the array could not be read");
        exit(EXIT_FAILURE);
    }

    return array;
}

int* crew_prefix_wrapper(int* array, size_t array_size) {
    int* result = malloc(array_size * sizeof(int));

    if (!result) {
        fputs("memory for the prefix array could not be allocated", stderr);
        exit(EXIT_FAILURE);
    }

    PERF_TIME(crew_prefix(array, array_size, result), "CREW Prefix");

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

CmdArgs parse_args(int argc, char** argv) {
    CmdArgs args = {
      .need_print = false,
    };

    if (argc > 2) {
        print_usage(basename(argv[0]));
        exit(EXIT_FAILURE);
    }

    if (!strcmp(argv[1], "-p") || !strcmp(argv[1], "--print")) {
        args.need_print = true;
    } else if (strcmp(argv[1], "")) {
        print_usage(basename(argv[0]));
        exit(EXIT_FAILURE);
    }

    return args;
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
