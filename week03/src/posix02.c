#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#include <pthread.h>

#define N_THREADS 60

void* other_thread(void* args) {
    Sleep(1000);
    return 0;
}

int main(int argc, char** argv) {
    pthread_t threads[N_THREADS] = {0};

    clock_t start = clock();

    for (size_t i = 0; i < N_THREADS; i++) {
        pthread_create(&threads[i], 0, other_thread, 0);
        printf("Thread %zu created\n", i);
    }

    for (size_t i = 0; i < N_THREADS; i++) {
        pthread_join(threads[i], 0);
        printf("Thread %zu joined\n", i);
    }

    clock_t diff = clock() - start;

    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken: %d seconds %d milliseconds\n", msec / 1000, msec % 1000);

    return EXIT_SUCCESS;
}
