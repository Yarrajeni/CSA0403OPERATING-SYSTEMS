#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function to be executed by thread 1
void *thread_func1(void *arg) {
    printf("Thread 1 is running.\n");
    return NULL;
}

// Function to be executed by thread 2
void *thread_func2(void *arg) {
    printf("Thread 2 is running.\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2;  // Thread identifiers

    // Create thread 1
    if (pthread_create(&thread1, NULL, thread_func1, NULL)) {
        perror("Error creating thread 1");
        return 1;
    }

    // Create thread 2
    if (pthread_create(&thread2, NULL, thread_func2, NULL)) {
        perror("Error creating thread 2");
        return 1;
    }

    // Wait for thread 1 to finish
    if (pthread_join(thread1, NULL)) {
        perror("Error joining thread 1");
        return 1;
    }

    // Wait for thread 2 to finish
    if (pthread_join(thread2, NULL)) {
        perror("Error joining thread 2");
        return 1;
    }

    printf("Both threads have finished.\n");

    return 0;
}
