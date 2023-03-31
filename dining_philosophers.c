#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_PHILOSOPHERS 5

sem_t chopsticks[NUM_PHILOSOPHERS];

void* philosopher(void* arg) {
    int philosopher_num = (int)arg;
    int left_chopstick = philosopher_num;
    int right_chopstick = (philosopher_num + 1) % NUM_PHILOSOPHERS;

    while(1) {
        printf("Philosopher %d is thinking\n", philosopher_num);
        sleep(1);

        sem_wait(&chopsticks[left_chopstick]);
        printf("Philosopher %d picked up left chopstick %d\n", philosopher_num, left_chopstick);

        sem_wait(&chopsticks[right_chopstick]);
        printf("Philosopher %d picked up right chopstick %d\n", philosopher_num, right_chopstick);

        printf("Philosopher %d is eating\n", philosopher_num);
        sleep(1);

        sem_post(&chopsticks[left_chopstick]);
        printf("Philosopher %d put down left chopstick %d\n", philosopher_num, left_chopstick);

        sem_post(&chopsticks[right_chopstick]);
        printf("Philosopher %d put down right chopstick %d\n", philosopher_num, right_chopstick);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t philosopher_threads[NUM_PHILOSOPHERS];

    for(int i=0; i<NUM_PHILOSOPHERS; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }

    for(int i=0; i<NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosopher_threads[i], NULL, philosopher, (void*)i);
    }

    for(int i=0; i<NUM_PHILOSOPHERS; i++) {
        pthread_join(philosopher_threads[i], NULL);
    }

    for(int i=0; i<NUM_PHILOSOPHERS; i++) {
        sem_destroy(&chopsticks[i]);
    }

    return 0;
}
