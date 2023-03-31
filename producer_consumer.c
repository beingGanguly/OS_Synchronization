#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int next_producer_index = 0;
int next_consumer_index = 0;

sem_t mutex;
sem_t empty;
sem_t full;

void* producer(void* arg) {
    int produced_items = 0;
    int item = 1;
    while(produced_items < BUFFER_SIZE) {
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[next_producer_index] = item;
        printf("Producer produced item %d at index %d\n", item, next_producer_index);
        next_producer_index = (next_producer_index + 1) % BUFFER_SIZE;
        produced_items++;

        sem_post(&mutex);
        sem_post(&full);

        item++;
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    int consumed_items = 0;
    while(consumed_items < BUFFER_SIZE) {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[next_consumer_index];
        printf("Consumer consumed item %d at index %d\n", item, next_consumer_index);
        next_consumer_index = (next_consumer_index + 1) % BUFFER_SIZE;
        consumed_items++;

        sem_post(&mutex);
        sem_post(&empty);
    }
    pthread_exit(NULL);
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
