// two_philosophers.c

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t fork1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fork2 = PTHREAD_MUTEX_INITIALIZER;

void* philosopher(void* arg) {
    int id = *(int*)arg;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(1); // Simulate thinking

        // Asymmetric lock order to prevent deadlock
        if (id == 0) {
            pthread_mutex_lock(&fork1);
            pthread_mutex_lock(&fork2);
        } else {
            pthread_mutex_lock(&fork2);
            pthread_mutex_lock(&fork1);
        }

        printf("Philosopher %d is eating...\n", id);
        sleep(2); // Simulate eating

        pthread_mutex_unlock(&fork1);
        pthread_mutex_unlock(&fork2);

        printf("Philosopher %d is done eating.\n", id);
    }
    return NULL;
}

int main() {
    pthread_t philosophers[2];
    int ids[2] = {0, 1};

    for (int i = 0; i < 2; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
