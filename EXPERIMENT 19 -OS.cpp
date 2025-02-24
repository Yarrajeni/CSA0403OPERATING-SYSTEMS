#include <stdio.h>
#include <pthread.h>

int counter = 0;  // Shared counter
pthread_mutex_t mutex;  // Mutex lock for synchronization

// Function to simulate a process that increments the counter
void* increment(void* arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mutex);  // Lock the mutex before modifying the counter
        counter++;  // Increment the shared counter
        pthread_mutex_unlock(&mutex);  // Unlock the mutex after modifying the counter
    }
    return NULL;
}

// Function to simulate another process that increments the counter
void* decrement(void* arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mutex);  // Lock the mutex before modifying the counter
        counter--;  // Decrement the shared counter
        pthread_mutex_unlock(&mutex);  // Unlock the mutex after modifying the counter
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Initialize the mutex lock
    pthread_mutex_init(&mutex, NULL);

    // Create two threads: one for incrementing and one for decrementing
    pthread_create(&thread1, NULL, increment, NULL);
    pthread_create(&thread2, NULL, decrement, NULL);

    // Wait for both threads to complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Print the final value of the counter
    printf("Final counter value: %d\n", counter);

    // Destroy the mutex lock
    pthread_mutex_destroy(&mutex);

    return 0;
}
