#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_THREADS 10

int sum = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// to enable mutual exclusion, set this variable to true.
// otherwise, the program will account for race conditions
// and generate a seemingly random number.
bool mutual_exclusion = false;

void *increment1000(void *arg) {
    if(mutual_exclusion) {
    pthread_mutex_lock(&mutex);
    }
    for(int x = 0; x < 1000; x++) {
        sum = sum + 1;
    }
    if(mutual_exclusion) {
    pthread_mutex_unlock(&mutex);
    }
    printf("Thread complete. Current sum: %d\n", sum);
    return NULL;
}

int main() {

    pthread_t threads[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment1000, NULL);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final value of sum: %d\n", sum);

    return 0;
}
