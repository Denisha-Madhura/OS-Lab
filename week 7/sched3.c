#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THINKING 0
#define HUNGRY 1
#define EATING 2

int n;
int *state;
pthread_mutex_t mutex;
pthread_cond_t *cond;

int left(int i) { return (i + n - 1) % n; }
int right(int i) { return (i + 1) % n; }

void test(int i) {
    if (state[i] == HUNGRY && state[left(i)] != EATING && state[right(i)] != EATING) {
        state[i] = EATING;
        pthread_cond_signal(&cond[i]);
    }
}

void pickup(int i) {
    pthread_mutex_lock(&mutex);
    state[i] = HUNGRY;
    test(i);
    while (state[i] != EATING)
        pthread_cond_wait(&cond[i], &mutex);
    pthread_mutex_unlock(&mutex);
}

void putdown(int i) {
    pthread_mutex_lock(&mutex);
    state[i] = THINKING;
    test(left(i));
    test(right(i));
    pthread_mutex_unlock(&mutex);
}

void *philosopher(void *arg) {
    int i = *((int *)arg);
    while (1) {
        printf("Philosopher %d is thinking\n", i);
        sleep(1);
        pickup(i);
        printf("Philosopher %d is eating\n", i);
        sleep(2);
        putdown(i);
    }
    return NULL;
}

int main() {
    printf("Enter number of philosophers: ");
    scanf("%d", &n);
    state = malloc(n * sizeof(int));
    cond = malloc(n * sizeof(pthread_cond_t));

    pthread_t *philosophers = malloc(n * sizeof(pthread_t));
    int *ids = malloc(n * sizeof(int));

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < n; i++) {
        pthread_cond_init(&cond[i], NULL);
        state[i] = THINKING;
    }

    for (int i = 0; i < n; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < n; i++)
        pthread_join(philosophers[i], NULL);

    free(state);
    free(cond);
    free(philosophers);
    free(ids);
    pthread_mutex_destroy(&mutex);
    return 0;
}

