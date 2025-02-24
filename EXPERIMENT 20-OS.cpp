#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_READERS 5
#define MAX_WRITERS 2

sem_t mutex, write_lock;
int read_count = 0, data = 0;

void* reader(void* arg) {
    int id = *(int*)arg;
    while (1) {
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) sem_wait(&write_lock);
        sem_post(&mutex);
        
        printf("Reader %d: Read data %d\n", id, data);

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) sem_post(&write_lock);
        sem_post(&mutex);
        sleep(1);
    }
}

void* writer(void* arg) {
    int id = *(int*)arg;
    while (1) {
        sem_wait(&write_lock);
        data++;
        printf("Writer %d: Write data %d\n", id, data);
        sem_post(&write_lock);
        sleep(2);
    }
}

int main() {
    pthread_t readers[MAX_READERS], writers[MAX_WRITERS];
    int reader_ids[MAX_READERS], writer_ids[MAX_WRITERS];

    sem_init(&mutex, 0, 1);
    sem_init(&write_lock, 0, 1);

    for (int i = 0; i < MAX_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    for (int i = 0; i < MAX_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < MAX_READERS; i++) pthread_join(readers[i], NULL);
    for (int i = 0; i < MAX_WRITERS; i++) pthread_join(writers[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&write_lock);
    return 0;
}
