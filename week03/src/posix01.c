#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#include <pthread.h>

pthread_mutex_t printf_mutex = PTHREAD_MUTEX_INITIALIZER;

void* main_thread(void* args) {
    char THREAD_NAME[] = "MAIN";
    int const COMPUTE_TIME = 8;

    for (int i = 0; i < COMPUTE_TIME; i++) {
        Sleep(1000);
        pthread_mutex_lock(&printf_mutex);
        printf("[%s] Computing... (Elapsed: %d seconds)\n", THREAD_NAME, i + 1);
        pthread_mutex_unlock(&printf_mutex);
    }

    return 0;
}

void* other_thread(void* args) {
    char THREAD_NAME[] = "OTHER";
    int const COMPUTE_TIME = 4;

    for (int i = 0; i < COMPUTE_TIME; i++) {
        Sleep(1000);
        pthread_mutex_lock(&printf_mutex);
        printf("[%s] Computing... (Elapsed: %d seconds)\n", THREAD_NAME, i + 1);
        pthread_mutex_unlock(&printf_mutex);
    }

    return 0;
}

int main(int argc, char** argv) {
    pthread_t thread = {0};
    pthread_create(&thread, 0, other_thread, 0);
    puts("Thread created");

    main_thread(0);

    pthread_join(thread, 0);
    puts("Thread joined");

    return EXIT_SUCCESS;
}
