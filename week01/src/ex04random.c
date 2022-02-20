#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand_interval(int min, int max);
double frand_interval(int min, int max);

int main(void) {
    srand(time(0));

    int const MIN = 500;
    int const MAX = 1000;

    printf("Integer in range [%d, %d]: %d\n", MIN, MAX, rand_interval(MIN, MAX));
    printf("Double in range [%d, %d]: %g\n", MIN, MAX, frand_interval(MIN, MAX));

    return EXIT_SUCCESS;
}

int rand_interval(int min, int max) {
    int range = max - min;
    return min + rand() % (range + 1);
}

double frand_interval(int min, int max) {
    int range = max - min;
    return min + (double) rand() / RAND_MAX * range;
}
