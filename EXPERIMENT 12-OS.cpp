#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5  // Number of philosophers

// Mutexes for each fork
pthread_mutex_t forks[NUM_PHILOSOPHERS];

// Simulate philosopher's behavior
void *philosopher(void *num) {
    int philosopher_num = *((int *)num);
    int left_fork = philosopher_num;
    int right_fork = (philosopher_num + 1) % NUM_PHILOSOPHERS;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking.\n", philosopher_num);
        usleep(rand() % 1000);  // Simulate thinking time

        // Picking up the left fork
        printf("Philosopher %d is picking up left fork %d.\n", philosopher_num, left_fork);
        pthread_mutex_lock(&forks[left_fork]);

        // Picking up the right fork
        printf("Philosopher %d is picking up right fork %d.\n", philosopher_num, right_fork);
        pthread_mutex_lock(&forks[right_fork]);

        // Eating
        printf("Philosopher %d is eating.\n", philosopher_num);
        usleep(rand() % 1000);  // Simulate eating time

        // Putting down the right fork
        printf("Philosopher %d is putting down right fork %d.\n", philosopher_num, right_fork);
        pthread_mutex_unlock(&forks[right_fork]);

        // Putting down the left fork
        printf("Philosopher %d is putting down left fork %d.\n", philosopher_num, left_fork);
        pthread_mutex_unlock(&forks[left_fork]);
    }
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_numbers[NUM_PHILOSOPHERS];

    // Initialize mutexes for each fork
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_numbers[i] = i;
        if (pthread_create(&philosophers[i], NULL, philosopher, (void *)&philosopher_numbers[i])) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Join philosopher threads (this never ends, as philosophers keep thinking and eating)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Clean up mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
