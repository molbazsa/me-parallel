#ifndef GUARD_E397A971_887D_42BA_9A20_6C4D2FB172A4
#define GUARD_E397A971_887D_42BA_9A20_6C4D2FB172A4

#include <stdbool.h>
#include <time.h>

#define PERF_TIME(f, s)                                                        \
    do {                                                                       \
        printf("Timing: %s\n", s);                                             \
        clock_t PERF_TIME_start = clock();                                     \
        f;                                                                     \
        clock_t PERF_TIME_diff = clock() - PERF_TIME_start;                    \
        long PERF_TIME_msec = PERF_TIME_diff * 1000 / CLOCKS_PER_SEC;          \
        printf("Time taken: %ld seconds %ld milliseconds\n",                   \
               PERF_TIME_msec / 1000,                                          \
               PERF_TIME_msec % 1000);                                         \
    } while (false)

#define PERF_TIME_STORE(f, s, p)                                               \
    do {                                                                       \
        printf("Timing: %s\n", s);                                             \
        clock_t PERF_TIME_start = clock();                                     \
        f;                                                                     \
        clock_t PERF_TIME_diff = clock() - PERF_TIME_start;                    \
        long PERF_TIME_msec = PERF_TIME_diff * 1000 / CLOCKS_PER_SEC;          \
        printf("Time taken: %ld seconds %ld milliseconds\n",                   \
               PERF_TIME_msec / 1000,                                          \
               PERF_TIME_msec % 1000);                                         \
        *(p) = PERF_TIME_msec;                                                 \
    } while (false)

#endif // GUARD_E397A971_887D_42BA_9A20_6C4D2FB172A4
